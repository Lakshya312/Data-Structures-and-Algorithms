#!/usr/bin/env python3
"""
import_leetcode_submissions.py

Bulk-imports your already-Accepted LeetCode submissions into a local git repo,
using the same "0044-Two-Sum/" folder convention that LeetHub v2 uses -- so this
script and LeetHub can coexist without conflicts (LeetHub takes over for new
solves, this script backfills the old ones once).

WHAT IT DOES
1. Logs into LeetCode using your browser session cookie (no password needed).
2. Walks your submission history, keeping only Accepted submissions,
   one (the most recent) per problem.
3. Fetches problem metadata (difficulty, tags, description link) for each.
4. Writes each solution to  <repo>/NNNN-Problem-Title/solution.cpp
   plus a small README.md in that folder with the problem link, difficulty
   and tags.
5. Makes one git commit per problem (so your commit history looks like you
   solved them one at a time), then a single `git push` at the end.
6. Caches everything it fetches into leetcode_data.json so the README
   generator script can reuse it without hitting the API again.

BEFORE YOU RUN THIS
--------------------
1. `pip install requests --break-system-packages` (if you don't have it)
2. Get your LeetCode session cookie:
   - Open leetcode.com in Chrome, log in, open DevTools (F12)
   - Application tab -> Cookies -> https://leetcode.com
   - Copy the value of the cookie named  LEETCODE_SESSION
   - Also copy the value of  csrftoken
3. Point this script at your local clone of the GitHub repo you created.

USAGE
-----
    export LEETCODE_SESSION="paste_value_here"
    export CSRF_TOKEN="paste_value_here"
    python3 import_leetcode_submissions.py /path/to/your/local/repo

    # dry run first (no writes, no commits) to sanity check what it will do:
    python3 import_leetcode_submissions.py /path/to/your/local/repo --dry-run
"""

import os
import re
import sys
import json
import time
import argparse
import subprocess
from pathlib import Path

import requests

LEETCODE_BASE = "https://leetcode.com"
GRAPHQL_URL = f"{LEETCODE_BASE}/graphql"

LANG_EXT = {
    "cpp": "cpp", "c": "c", "python": "py", "python3": "py",
    "java": "java", "javascript": "js", "typescript": "ts",
    "csharp": "cs", "golang": "go", "kotlin": "kt", "swift": "swift",
    "rust": "rs", "ruby": "rb", "scala": "scala", "php": "php",
}


def get_session():
    session_cookie = os.environ.get("LEETCODE_SESSION")
    csrf_token = os.environ.get("CSRF_TOKEN")
    if not session_cookie or not csrf_token:
        sys.exit(
            "ERROR: set LEETCODE_SESSION and CSRF_TOKEN environment variables first "
            "(see the docstring at the top of this file for how to get them)."
        )
    s = requests.Session()
    s.cookies.set("LEETCODE_SESSION", session_cookie, domain="leetcode.com")
    s.cookies.set("csrftoken", csrf_token, domain="leetcode.com")
    s.headers.update({
        "Referer": "https://leetcode.com",
        "x-csrftoken": csrf_token,
        "User-Agent": "Mozilla/5.0",
    })
    return s


def fetch_all_accepted_submissions(session, max_pages=200):
    """Paginate through /api/submissions/ and keep the most recent Accepted
    submission per problem (by title)."""
    seen = {}
    offset = 0
    limit = 20
    for _ in range(max_pages):
        url = f"{LEETCODE_BASE}/api/submissions/?offset={offset}&limit={limit}"
        resp = session.get(url, timeout=15)
        if resp.status_code != 200:
            print(f"  ! stopped paginating (HTTP {resp.status_code}) at offset {offset}")
            break
        data = resp.json()
        subs = data.get("submissions_dump", [])
        if not subs:
            break
        for sub in subs:
            if sub.get("status_display") != "Accepted":
                continue
            title = sub["title"]
            # keep first-seen == most recent, since API returns newest first
            if title not in seen:
                seen[title] = sub
        offset += limit
        if not data.get("has_next"):
            break
        time.sleep(0.4)  # be polite to LeetCode's servers
    return list(seen.values())


def fetch_question_metadata(session, title_slug):
    query = """
    query questionData($titleSlug: String!) {
      question(titleSlug: $titleSlug) {
        questionFrontendId
        title
        titleSlug
        difficulty
        topicTags { name }
      }
    }
    """
    resp = session.post(
        GRAPHQL_URL,
        json={"query": query, "variables": {"titleSlug": title_slug}},
        timeout=15,
    )
    resp.raise_for_status()
    return resp.json()["data"]["question"]


def slugify_title(title):
    # "Two Sum" -> "Two-Sum"
    return re.sub(r"[^a-zA-Z0-9]+", "-", title).strip("-")


def guess_title_slug(sub):
    # the /api/submissions/ payload doesn't include title_slug directly on
    # older LeetCode responses, so derive it the same way LeetCode does
    return sub["title"].lower()
    # (overridden below by using the sub's own 'title_slug' key when present)


def run_git(repo_path, args, dry_run):
    cmd = ["git"] + args
    if dry_run:
        print(f"  [dry-run] git {' '.join(args)}")
        return
    subprocess.run(cmd, cwd=repo_path, check=True)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("repo_path", help="Path to your local git clone of the DSA repo")
    ap.add_argument("--dry-run", action="store_true", help="Preview without writing/committing")
    ap.add_argument("--no-push", action="store_true", help="Commit locally but skip git push")
    args = ap.parse_args()

    repo_path = Path(args.repo_path).expanduser().resolve()
    if not args.dry_run and not (repo_path / ".git").exists():
        sys.exit(f"ERROR: {repo_path} doesn't look like a git repo (no .git folder).")

    session = get_session()

    print("Fetching your Accepted submissions from LeetCode...")
    submissions = fetch_all_accepted_submissions(session)
    print(f"Found {len(submissions)} unique solved problems.")

    cache = {}
    imported = 0

    for sub in submissions:
        title = sub["title"]
        title_slug = sub.get("title_slug") or slugify_title(title).lower()
        lang = sub.get("lang", "cpp")
        ext = LANG_EXT.get(lang, "txt")
        code = sub.get("code", "")

        try:
            meta = fetch_question_metadata(session, title_slug)
        except Exception as e:
            print(f"  ! couldn't fetch metadata for '{title}': {e}")
            continue

        if not meta:
            print(f"  ! no metadata found for '{title}', skipping")
            continue

        qid = meta["questionFrontendId"].zfill(4)
        tags = [t["name"] for t in meta["topicTags"]]
        difficulty = meta["difficulty"]
        folder_name = f"{qid}-{slugify_title(meta['title'])}"
        folder_path = repo_path / folder_name

        cache[folder_name] = {
            "id": qid,
            "title": meta["title"],
            "difficulty": difficulty,
            "tags": tags,
            "slug": title_slug,
        }

        print(f"  -> {folder_name}  [{difficulty}]  tags: {', '.join(tags) or 'none'}")

        if args.dry_run:
            imported += 1
            continue

        folder_path.mkdir(parents=True, exist_ok=True)
        (folder_path / f"solution.{ext}").write_text(code + "\n")
        readme = (
            f"# {qid}. {meta['title']}\n\n"
            f"**Difficulty:** {difficulty}\n\n"
            f"**Tags:** {', '.join(tags) if tags else '_none_'}\n\n"
            f"**Problem:** https://leetcode.com/problems/{title_slug}/\n"
        )
        (folder_path / "README.md").write_text(readme)

        run_git(repo_path, ["add", str(folder_path.relative_to(repo_path))], args.dry_run)
        run_git(
            repo_path,
            ["commit", "-m", f"Add solution: {qid} {meta['title']} ({difficulty})"],
            args.dry_run,
        )
        imported += 1
        time.sleep(0.3)

    if not args.dry_run:
        cache_file = repo_path / "leetcode_data.json"
        existing = {}
        if cache_file.exists():
            existing = json.loads(cache_file.read_text())
        existing.update(cache)
        cache_file.write_text(json.dumps(existing, indent=2))
        run_git(repo_path, ["add", "leetcode_data.json"], args.dry_run)
        run_git(repo_path, ["commit", "-m", "Update leetcode_data.json cache"], args.dry_run)

        if not args.no_push:
            print("Pushing to GitHub...")
            run_git(repo_path, ["push"], args.dry_run)

    print(f"\nDone. Imported {imported} problems.")
    if args.dry_run:
        print("(This was a dry run -- nothing was written or committed.)")


if __name__ == "__main__":
    main()

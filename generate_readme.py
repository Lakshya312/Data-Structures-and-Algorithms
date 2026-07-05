#!/usr/bin/env python3
"""
generate_readme.py

Scans your DSA repo (folders named like "0044-Two-Sum") plus the
leetcode_data.json cache written by import_leetcode_submissions.py, and
(re)generates a polished README.md with:
  - a header + badges
  - solved count and a difficulty breakdown
  - a topics-covered tag cloud
  - a full table of every problem, linked back to LeetCode and to your solution

Safe to re-run any time (e.g. after LeetHub syncs new problems in) to
refresh the README. It only ever touches README.md.

USAGE
-----
    python3 generate_readme.py /path/to/your/local/repo --name "Lakshya" --lang cpp
"""

import re
import json
import argparse
from pathlib import Path
from collections import Counter, defaultdict

FOLDER_RE = re.compile(r"^(\d{4})-(.+)$")

DIFFICULTY_EMOJI = {"Easy": "🟢", "Medium": "🟡", "Hard": "🔴"}


def load_cache(repo_path):
    cache_file = repo_path / "leetcode_data.json"
    if cache_file.exists():
        return json.loads(cache_file.read_text())
    return {}


def discover_folders(repo_path):
    folders = []
    for p in sorted(repo_path.iterdir()):
        if p.is_dir() and FOLDER_RE.match(p.name):
            folders.append(p.name)
    return folders


def make_badge(label, value, color):
    label_enc = label.replace(" ", "%20")
    value_enc = str(value).replace(" ", "%20")
    return f"![{label}](https://img.shields.io/badge/{label_enc}-{value_enc}-{color}?style=for-the-badge)"


def build_readme(repo_path, cache, folders, owner_name, lang):
    total = len(folders)
    diff_counter = Counter()
    tag_counter = Counter()
    rows = []

    for folder in folders:
        m = FOLDER_RE.match(folder)
        qid, title_slug = m.group(1), m.group(2)
        meta = cache.get(folder, {})
        title = meta.get("title", title_slug.replace("-", " "))
        difficulty = meta.get("difficulty", "Unknown")
        tags = meta.get("tags", [])
        slug = meta.get("slug", title_slug.lower())

        diff_counter[difficulty] += 1
        for t in tags:
            tag_counter[t] += 1

        emoji = DIFFICULTY_EMOJI.get(difficulty, "⚪")
        primary_tag = tags[0] if tags else "-"
        rows.append(
            f"| {qid} | [{title}](https://leetcode.com/problems/{slug}/) "
            f"| {emoji} {difficulty} | {primary_tag} | [Solution]({folder}/) |"
        )

    easy = diff_counter.get("Easy", 0)
    med = diff_counter.get("Medium", 0)
    hard = diff_counter.get("Hard", 0)

    top_tags = [t for t, _ in tag_counter.most_common(12)]
    tag_line = " ".join(f"`{t}`" for t in top_tags) if top_tags else "_add more solutions to see topics here_"

    header = f"""<div align="center">

# 🧠 {owner_name}'s DSA Journey

### LeetCode solutions, synced straight from the source.

{make_badge("Solved", total, "brightgreen")} {make_badge("Language", lang.upper(), "blue")} {make_badge("Auto--Synced", "LeetHub", "orange")}

</div>

---

## 📊 Progress

| 🟢 Easy | 🟡 Medium | 🔴 Hard | **Total** |
|:---:|:---:|:---:|:---:|
| {easy} | {med} | {hard} | **{total}** |

## 🏷️ Topics Covered

{tag_line}

## ⚙️ How this repo works

Every problem I solve on LeetCode is auto-committed here via
[LeetHub v2](https://github.com/arunbhardwaj/LeetHub-2.0) the moment it's Accepted —
code, problem link, and stats included. No manual copy-pasting.

Each folder is named `<problem-number>-<Problem-Title>` and contains:
- `solution.{lang}` — the accepted solution
- `README.md` — problem link, difficulty, and tags

## 📚 All Solutions

| # | Problem | Difficulty | Topic | Link |
|---|---------|------------|-------|------|
"""
    footer = f"""

---

<div align="center">
Made with ⚡ and a lot of debugging · Last updated automatically
</div>
"""
    return header + "\n".join(rows) + footer


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("repo_path")
    ap.add_argument("--name", default="My", help="Your name, for the header")
    ap.add_argument("--lang", default="cpp", help="Primary language used")
    args = ap.parse_args()

    repo_path = Path(args.repo_path).expanduser().resolve()
    cache = load_cache(repo_path)
    folders = discover_folders(repo_path)

    readme = build_readme(repo_path, cache, folders, args.name, args.lang)
    (repo_path / "README.md").write_text(readme)
    print(f"README.md written with {len(folders)} problems listed.")


if __name__ == "__main__":
    main()

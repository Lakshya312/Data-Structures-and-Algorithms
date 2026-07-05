# LeetCode → GitHub Setup Guide

## Step 1 — Auto-sync future submissions (LeetHub v2)

1. Install **LeetHub v2**:
   - Chrome: search "LeetHub v2" on the Chrome Web Store, or grab it from
     https://github.com/arunbhardwaj/LeetHub-2.0
   - Firefox: "LeetHub 2.0 for Firefox" on addons.mozilla.org
2. Click the extension icon → **Authorize with GitHub**.
3. Pick (or create) your DSA repo as the sync target.
4. That's it. From now on, every time you get "Accepted" on LeetCode, it
   auto-commits `NNNN-Problem-Title/solution.cpp` + the problem description
   to that repo within seconds. No more manual copy-paste.

## Step 2 — Backfill your 44 already-solved problems

This part LeetHub can't do retroactively, so use the import script:

1. Clone your repo locally if you haven't:
   ```bash
   git clone https://github.com/<you>/<your-repo>.git
   ```
2. Install the one dependency:
   ```bash
   pip install requests --break-system-packages
   ```
3. Grab your LeetCode session cookie (one-time, takes 30 seconds):
   - Log into leetcode.com in Chrome
   - Open DevTools (F12) → Application tab → Cookies → `https://leetcode.com`
   - Copy the values of `LEETCODE_SESSION` and `csrftoken`
4. Run it:
   ```bash
   export LEETCODE_SESSION="paste_here"
   export CSRF_TOKEN="paste_here"

   # sanity check first, writes nothing:
   python3 import_leetcode_submissions.py /path/to/your-repo --dry-run

   # then for real:
   python3 import_leetcode_submissions.py /path/to/your-repo
   ```
   It will fetch your Accepted submissions, recreate each one in the same
   `NNNN-Problem-Title/` format LeetHub uses, commit them one problem at a
   time (so your commit graph looks natural), then push everything.

   > Your session cookie can expire — if the script starts getting 401/403
   > errors, just grab a fresh one from DevTools and re-export it.

## Step 3 — Generate the README

```bash
python3 generate_readme.py /path/to/your-repo --name "Lakshya" --lang cpp
```

This builds a README with a progress table (Easy/Medium/Hard breakdown), a
topics tag cloud, and a full linked table of every solved problem — reading
straight from the folders + the `leetcode_data.json` cache the import script
created.

Re-run it any time (weekly, or after a solving streak) to keep it fresh —
it only touches `README.md`, never your solutions.

## Order of operations, in one line

**Install LeetHub → backfill the 44 with the import script → generate the
README → commit & push the README.**

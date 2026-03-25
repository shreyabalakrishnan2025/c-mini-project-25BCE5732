# Expense Tracker

A web-based frontend for a C expense tracker program. The frontend replicates all logic from `main.c` in JavaScript and runs entirely in the browser — no server needed.

## Features

| Feature | Description |
|---|---|
| Add Expense | Validated date (year/month/day), category, amount, note |
| Show All | Table of every recorded expense |
| Monthly Total | Sum for a given month with budget warning |
| Category Total | Sum for a given category |
| Search by Date | Filter records by exact date |
| Search by Category | Filter records by category |
| Overview | Dashboard with stats and budget progress bar |

## Running Locally

Just open `index.html` in any browser — no build step, no server required.

```bash
# Option 1: double-click index.html

# Option 2: quick local server
npx serve .
# or
python3 -m http.server 8080
```

## Hosting on GitHub Pages

1. Push this repo to GitHub
2. Go to **Settings → Pages**
3. Set Source to **main branch / root**
4. Your site will be live at `https://<username>.github.io/<repo>/`

## Data Storage

Expenses are stored in `localStorage` in your browser. Data persists across page refreshes but is local to your browser/device.

## Files

```
index.html   — complete frontend (single file, no dependencies)
main.c       — original C source (reference implementation)
README.md    — this file
```

## Tech Stack

- Vanilla HTML / CSS / JavaScript (zero dependencies)
- Google Fonts (Syne + Space Mono) loaded via CDN
- `localStorage` for persistence (equivalent to `expenses.txt`)

#!/usr/bin/env sh
set -eu

REPO_ROOT="$(dirname "$0")/.."

echo "[redeploy] Pulling latest changes from main..."
git -C "$REPO_ROOT" pull origin main

echo "[redeploy] Rebuilding and restarting containers..."
docker compose -f "$REPO_ROOT/docker-compose.yml" up --build -d

echo "[redeploy] Done."

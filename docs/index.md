# Sisyphos Game Engine

[![Build & Test](https://github.com/GameStracho/sisyphos/actions/workflows/build_test.yml/badge.svg)](https://github.com/GameStracho/sisyphos/actions/workflows/build_test.yml)
[![Release](https://github.com/GameStracho/sisyphos/actions/workflows/release.yml/badge.svg)](https://github.com/GameStracho/sisyphos/actions/workflows/release.yml)
[![License](https://img.shields.io/github/license/GameStracho/sisyphos)](https://github.com/GameStracho/sisyphos/blob/main/LICENSE)
[![Version](https://img.shields.io/github/v/release/GameStracho/sisyphos)](https://github.com/GameStracho/sisyphos/releases)

A universal, data-driven C++ game engine designed for building portable game SDKs with runtime Lua scripting.

The engine is intentionally free of game-specific logic — all game rules live in Lua scripts, assets are loaded from an external project folder, and the compiled SDK can be shipped as a plain ZIP archive.

---

## Features

- **OpenGL Renderer** — PBR materials, shadow mapping, and post-processing pipeline
- **ECS** — Entity and component management via [EnTT](https://github.com/skypjack/entt)
- **Physics** — Movement dynamics and collision detection via Bullet Physics
- **Spatial Partitioning** — BVH tree for frustum culling and mouse picking
- **3D Audio** — Spatial sound via OpenAL Soft
- **Scripting** — Lua + sol2 with hot-reload (no restart required)
- **UI System** — HTML/CSS game UI and HUD via RmlUi
- **Editor** — Dear ImGui-based tool with 3D gizmos and an integrated Lua code editor

---

## Getting Started

### Prerequisites

- CMake ≥ 3.25
- C++20 compiler (GCC, Clang, or MSVC)
- OpenGL driver

### Build

```bash
# 1. Clone the repository
git clone https://github.com/GameStracho/sisyphos.git
cd sisyphos

# 2. Configure
cmake --preset debug            # Debug — editor + launcher + tests (Linux/macOS)
cmake --preset release          # Release                           (Linux/macOS)
cmake --preset debug-windows    # Debug                             (Windows/Ninja)
cmake --preset release-windows  # Release                           (Windows/Ninja)

# Launcher-only presets (no editor / ImGui dependency)
cmake --preset debug-launcher
cmake --preset release-launcher

# 3. Build
cmake --build --preset debug-build
cmake --build --preset release-build

# 4. Run tests
ctest --preset debug-test
```

---

## Game Project Structure

Each game is a self-contained folder inside `games/`:

```
games/
└── MyGame/
    ├── assets/       # 3D models (.glb) and textures (.png)
    ├── scripts/      # Game logic (.lua)
    ├── scenes/       # Saved scenes (.json)
    ├── project.json  # Project metadata (name, entry script, asset paths)
    └── config.json   # User settings — created automatically at first launch
```

---

## Contributing

This project follows a simplified **GitFlow**:

| Branch        | Purpose                                     |
| ------------- | ------------------------------------------- |
| `main`        | Stable releases — direct commits disabled   |
| `develop`     | Integration branch for completed features   |
| `feat/<name>` | Short-lived feature branches, merged via PR |

Commit messages follow [Conventional Commits](https://www.conventionalcommits.org/) (`feat:`, `fix:`, `feat!:` for breaking changes). Every PR to `main` is gated by the CI pipeline (build + Google Test).

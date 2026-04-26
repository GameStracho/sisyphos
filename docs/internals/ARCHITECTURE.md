# 1. Architecture and Technology
The engine will be built as a **universal, data-driven system** that separates the high-performance core from the game content itself.

- **Core (C++)**: Performance, memory management, and low-level systems.
- **Graphics (OpenGL)**: Renderer with support for shadows, post-processing, and PBR materials.
- **Spatial Partitioning (BVH)**: Efficient scene management, frustum culling, and mouse picking.
- **ECS (EnTT)**: Management of objects (entities) and their data (components).
- **Physics (Bullet Physics)**: Vehicle dynamics (`btRaycastVehicle`) and collisions.
- **Audio (OpenAL Soft)**: Spatial 3D sound.
- **Scripting (Lua + sol2)**: Game logic that can be modified at runtime without compilation.
- **UI (RmlUi)**: Professional interface built on HTML/CSS for the game and HUD.
- **Editor (Dear ImGui)**: Standalone development tool with a code editor and gizmos.

# 2. Data Model and Formats
The game will be completely separated from the engine in a separate project folder.

- **3D Models**: **.glb** format (glTF 2.0) for geometry, PBR materials, and animations from Blender.
- **2D Graphics**: **.png** (sprite sheets) from Aseprite.
- **Serialization (Saving)**: A combination of **Cereal** (for binary/fast scene saving) and **nlohmann-json** (for configuration files and metadata).
- **Structure**: The project contains `project.json` (metadata) and `config.json` (graphics settings for the player).

# 3. Development Process (Git & GitHub)
This project uses a modified **GitFlow** within a single **monorepo** for maximum consistency.

- **Branches**:
    - `main`: Stable version, direct commits disabled, used for releases.
    - `develop`: Main integration branch for new features.
    - `feat/name`: Short-term branches for specific tasks, merged via Pull Requests (PRs).
- **Versioning**: Automated via **Semantic Versioning** and the **Conventional Commits** convention (feat:, fix:, feat!:).

# 4. Automation (CI/CD)
GitHub Actions handle the tedious work:

- **Check**: With every PR, the code is compiled and **unit and integration tests (Google Test)** are run.
- **Deployment**: When merged into `main`, a **GitHub Release** is automatically created.
- **SDK**: The pipeline generates a ZIP file (Artifact) containing the finished `.exe` files (Editor and Launcher), DLL libraries, and the Lua API—ready for immediate game development.

# 5. Documentation and Maintenance
The project will have a professional appearance both externally and internally.

- **README & LICENSE**: Basic information and MIT/GPL licenses in the root directory.
- **Hybrid documentation**: Written in **Markdown** in the `/docs` folder, automatically published as a website via **CloudFlare** (e.g., using MkDocs).
- **Technical documentation**: Generated directly from the code using **Doxygen**.

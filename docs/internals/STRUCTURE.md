/sisyphos (Root)
├── .github/                 # Automation
│   └── workflows/
│       ├── build_test.yml   # CI: Build and GTest
│       └── release.yml      # CD: Version update and SDK upload
├── cmake/                   # CMake helper scripts (e.g., FindBullet.cmake)
├── docs/                    # Markdown documentation (for MkDocs)
│   ├── user-guide/          # Editor user guides
│   ├── api/                 # Lua function reference
│   └── internals/           # Architecture notes (BVH, ECS)
├── src/                     # C++ source code
│   ├── engine/              # Engine core (static or shared library)
│   │   ├── include/         # Public header files (.h, .hpp)
│   │   └── src/             # Implementation (.cpp)
│   ├── editor/              # Editor application (links to the engine)
│   └── launcher/            # Stripped-down game player (links to the engine)
├── tests/                   # Unit and integration tests (Google Test)
├── third-party/             # External libraries
│   ├── vcpkg/
│   ├── vcpkg_installed/
├── games/                   # Folders containing specific games (user projects)
│   └── Snake2D/             # Sample project
│       ├── assets/          # .glb models, .png textures
│       ├── scripts/         # .lua scripts
│       ├── scenes/          # .json scene files
│       ├── project.json     # Project metadata
│       └── config.json      # User settings (created by the engine at startup)
├── .env.example             # Example of configuration for Documentation Website hosting
├── .gitignore               # Ignored files (build/, .vs/, etc.)
├── CMakeLists.txt           # Main CMake configuration file
├── docker-compose.yml       # Services for hosting Documentation Website
├── Dockerfile               # Documentation Website container
├── LICENSE
├── .mkdocs.yml              # MkDocs configuration
├── README.md                # Project welcome page
└── CHANGELOG.md             # Automatically generated list of changes

# Key points of this structure:
- **Separation** of the `engine` **and** `editor`: The editor is merely a "client" of the engine. This enables easy creation of a `launcher` (for players) later on that won't include the editor's cumbersome ImGui interface.
- **The `games/` folder**: Used for testing the engine in a real-world deployment. Each folder within it represents what a user would package as their game.
- **Relative paths**: All code in `engine` must assume that assets are searched for relative to the path defined in **project.json**.

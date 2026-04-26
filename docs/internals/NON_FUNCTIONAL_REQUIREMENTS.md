# 📈 Non-Functional Requirements
Non-Functional requirements define the quality, limitations, and technical standards of the system.

## 1. Performance and Efficiency
- **Frame Rate**: The engine must be able to render a scene with BVH and physics at a stable **60 FPS** on average hardware (e.g., an integrated GPU in a modern processor).
- **Startup Speed**: Loading the base scene from a binary format (via Cereal) must not take longer than **2 seconds**.

# 2. Architecture and Modularity
- **Separation of data and code**: All game content (assets, scripts) must be stored outside the engine’s binary files folder.
- **Versatility**: The engine must not have the logic of a specific game "hard-coded"; all game rules must be defined in Lua scripts.

# 3. Portability and Distribution
- **Compilability**: The source code must be compilable on both Windows and Linux platforms using CMake.
- **Installation Independence**: The resulting SDK must be "portable"—the user must be able to run it simply by unpacking the ZIP archive without needing to install system libraries.

# 4. Reliability and Quality
- **Test Coverage**: Key mathematical and logical modules (BVH, Transformations) must be covered by unit tests with 100% success rate.
- **CI/CD Stability**: Every Pull Request to the `main` branch must pass the automated build without errors.

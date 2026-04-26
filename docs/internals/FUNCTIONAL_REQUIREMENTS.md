# 🛠 Functional Requirements
Functional requirements define the specific behavior of the system and its interactions with the user.

## 1. Core and Scene Management
- **Asset Import**: The engine must support the import of 3D models in `.glb` format, including materials and textures.
- **ECS Architecture**: The system must allow for the creation, destruction, and modification of entities and their components at runtime.
- Spatial Optimization: The engine must use a BVH tree for scene culling (Frustum Culling) and collision acceleration.

## 2. Physics and Simulation
- **Vehicle Simulation**: The engine must include a physical model of a car with functional suspension, tire friction, and acceleration.
- **Collision Detection**: The system must detect collisions between the vehicle and the static environment (track).

## 3. Scripting and Logic
- **Lua API**: The engine must provide an API for controlling entities, physics, and the UI using Lua scripts.
- **Hot-reloading**: The engine must allow scripts to be reloaded without having to restart the entire application.

## 4. Editor and Tools
- **3D Manipulation**: The user must be able to pan, rotate, and scale objects using visual gizmos.
- **Project Serialization**: The engine must be able to save and load the entire scene state into JSON format.
- **Integrated Code Editor**: The editor must include a window for directly editing Lua scripts with syntax highlighting.

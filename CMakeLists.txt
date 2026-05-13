cmake_minimum_required(VERSION 3.25)

# vcpkg must be bootstrapped before project() so the toolchain is active
# during the first CMake configure run.
include(cmake/vcpkg.cmake)

project(sisyphos VERSION 0.0.1 LANGUAGES CXX)

# ---------------------------------------------------------------------------
# Global C++ standard
# ---------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------------------------------------------------------------------------
# Build options
# ---------------------------------------------------------------------------
option(BUILD_EDITOR   "Build the editor application"  ON)
option(BUILD_LAUNCHER "Build the launcher application" ON)
option(BUILD_TESTING  "Build unit and integration tests" ON)

# ---------------------------------------------------------------------------
# Compiler-specific sanitizer flags (debug builds only)
# Applied to all targets via an INTERFACE library so they propagate uniformly.
# ---------------------------------------------------------------------------
add_library(sisyphos_sanitizers INTERFACE)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(sisyphos_sanitizers INTERFACE /fsanitize=address)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(sisyphos_sanitizers INTERFACE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
        )
        target_link_options(sisyphos_sanitizers INTERFACE
            -fsanitize=address,undefined
        )
    endif()
endif()

# ---------------------------------------------------------------------------
# System dependencies (not managed by vcpkg)
# ---------------------------------------------------------------------------
find_package(OpenGL REQUIRED)

# ---------------------------------------------------------------------------
# vcpkg-managed dependencies (shared across engine, editor, launcher, tests)
# ---------------------------------------------------------------------------
find_package(EnTT         CONFIG REQUIRED)
find_package(Bullet       CONFIG REQUIRED)
find_package(Lua                 REQUIRED)
find_package(sol2         CONFIG REQUIRED)
find_package(OpenAL              REQUIRED)
find_package(RmlUi        CONFIG REQUIRED)
find_package(glfw3        CONFIG REQUIRED)
find_package(glad         CONFIG REQUIRED)
find_package(assimp       CONFIG REQUIRED)
find_package(cereal       CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(spdlog       CONFIG REQUIRED)
find_package(Stb          REQUIRED)
find_package(glm          CONFIG REQUIRED)

# ---------------------------------------------------------------------------
# Targets
# ---------------------------------------------------------------------------
add_subdirectory(src/engine)

if(BUILD_EDITOR)
    add_subdirectory(src/editor)
endif()

if(BUILD_LAUNCHER)
    add_subdirectory(src/launcher)
endif()

enable_testing()
include(CTest)

if(BUILD_TESTING)
    find_package(GTest CONFIG REQUIRED)
    add_subdirectory(tests)
endif()

# cmake/vcpkg.cmake
# Downloads and bootstraps vcpkg via FetchContent, then sets CMAKE_TOOLCHAIN_FILE.
# This file MUST be included before the project() call in the root CMakeLists.txt.
#
# The toolchain can be overridden from the command line:
#   cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/other/toolchain.cmake ...

if(DEFINED CMAKE_TOOLCHAIN_FILE)
    message(STATUS "[vcpkg] CMAKE_TOOLCHAIN_FILE already set — skipping vcpkg bootstrap.")
    return()
endif()

include(FetchContent)

FetchContent_Declare(
    vcpkg
    GIT_REPOSITORY https://github.com/microsoft/vcpkg.git
    GIT_TAG        2026.03.18
    GIT_SHALLOW    TRUE
    SOURCE_DIR     "${CMAKE_SOURCE_DIR}/third-party/vcpkg"
)

message(STATUS "[vcpkg] Fetching vcpkg...")
FetchContent_MakeAvailable(vcpkg)

# Bootstrap the vcpkg binary if it has not been built yet.
set(_vcpkg_dir "${CMAKE_SOURCE_DIR}/third-party/vcpkg")

if(CMAKE_HOST_WIN32)
    set(_vcpkg_bootstrap "${_vcpkg_dir}/bootstrap-vcpkg.bat")
    set(_vcpkg_exe       "${_vcpkg_dir}/vcpkg.exe")
else()
    set(_vcpkg_bootstrap "${_vcpkg_dir}/bootstrap-vcpkg.sh")
    set(_vcpkg_exe       "${_vcpkg_dir}/vcpkg")
endif()

if(NOT EXISTS "${_vcpkg_exe}")
    message(STATUS "[vcpkg] Bootstrapping vcpkg binary...")
    if(CMAKE_HOST_WIN32)
        execute_process(
            COMMAND cmd /C "${_vcpkg_bootstrap}" -disableMetrics
            WORKING_DIRECTORY "${_vcpkg_dir}"
            RESULT_VARIABLE _bootstrap_result
        )
    else()
        execute_process(
            COMMAND bash "${_vcpkg_bootstrap}" -disableMetrics
            WORKING_DIRECTORY "${_vcpkg_dir}"
            RESULT_VARIABLE _bootstrap_result
        )
    endif()

    if(NOT _bootstrap_result EQUAL 0)
        message(FATAL_ERROR "[vcpkg] Bootstrap failed (exit code ${_bootstrap_result}).")
    endif()
    message(STATUS "[vcpkg] Bootstrap complete.")
endif()

set(CMAKE_TOOLCHAIN_FILE
    "${_vcpkg_dir}/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "[vcpkg] Toolchain file set by cmake/vcpkg.cmake"
)

message(STATUS "[vcpkg] Toolchain: ${CMAKE_TOOLCHAIN_FILE}")

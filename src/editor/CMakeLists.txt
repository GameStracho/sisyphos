find_package(imgui CONFIG REQUIRED)

file(GLOB_RECURSE EDITOR_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(sisyphos_editor ${EDITOR_SOURCES})

# WIN32 suppresses the console window on Windows release builds.
if(WIN32)
    set_target_properties(sisyphos_editor PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

target_include_directories(sisyphos_editor
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(sisyphos_editor
    PRIVATE
        sisyphos_engine
        imgui::imgui
)

file(GLOB_RECURSE LAUNCHER_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(sisyphos_launcher ${LAUNCHER_SOURCES})

# WIN32 suppresses the console window on Windows release builds.
if(WIN32)
    set_target_properties(sisyphos_launcher PROPERTIES WIN32_EXECUTABLE $<CONFIG:Release>)
    target_link_options(sisyphos_launcher PRIVATE $<$<CONFIG:Release>:/ENTRY:mainCRTStartup>)
endif()

target_include_directories(sisyphos_launcher
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(sisyphos_launcher
    PRIVATE
        sisyphos_engine
)

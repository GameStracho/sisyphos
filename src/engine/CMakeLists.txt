file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(sisyphos_engine STATIC ${ENGINE_SOURCES})

target_include_directories(sisyphos_engine
    PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(sisyphos_engine
    PUBLIC
        OpenGL::GL
        EnTT::EnTT
        BulletDynamics
        BulletCollision
        LinearMath
        sol2::sol2
        ${LUA_LIBRARIES}
        OpenAL::OpenAL
        RmlUi::RmlUi
        glfw
        glad::glad
        assimp::assimp
        cereal::cereal
        nlohmann_json::nlohmann_json
        sisyphos_sanitizers
)

target_include_directories(sisyphos_engine PUBLIC ${LUA_INCLUDE_DIR})

// glad must be included before any other GL/GLFW headers.
#include <glad/glad.h>

#include <spdlog/spdlog.h>

#include "window.hpp"
#include "opengl/vao.hpp"
#include "opengl/vbo.hpp"
#include "opengl/shader.hpp"
#include "opengl/shaderprogram.hpp"
#include "opengl/texture.hpp"

int main()
{
#ifdef NDEBUG
    spdlog::set_level(spdlog::level::info);
#else
    spdlog::set_level(spdlog::level::debug);
#endif

    sisyphos::Window window{1280, 720, "Sisyphos"};

    // Interleaved vertex data: position (xyz) + UV (uv)
    constexpr float vertices[] = {
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,   0.5f, 1.0f,
    };

    sisyphos::opengl::VAO vao;
    sisyphos::opengl::VBO vbo;

    vao.bind();
    vbo.bind();
    vbo.upload(vertices, sizeof(vertices));

    // attribute 0 — position
    vao.setAttribPointer(0, 3, sisyphos::opengl::AttribType::Float, false,
                         5 * sizeof(float), reinterpret_cast<const void*>(0));
    vao.enableAttrib(0);

    // attribute 1 — UV
    vao.setAttribPointer(1, 2, sisyphos::opengl::AttribType::Float, false,
                         5 * sizeof(float), reinterpret_cast<const void*>(3 * sizeof(float)));
    vao.enableAttrib(1);

    vao.unbind();

    sisyphos::opengl::Shader vert{sisyphos::opengl::ShaderStage::Vertex,   "shaders/triangle.vert"};
    sisyphos::opengl::Shader frag{sisyphos::opengl::ShaderStage::Fragment, "shaders/triangle.frag"};
    sisyphos::opengl::ShaderProgram program{vert.getId(), frag.getId()};

    sisyphos::opengl::Texture texture{"assets/test_texture.png"};

    program.use();
    program.set<int>(0, 0); // location 0 - texture unit 0

    while (!window.shouldClose())
    {
        window.pollEvents();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        texture.bind(0);

        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        vao.unbind();

        window.swapBuffers();
    }

    return 0;
}

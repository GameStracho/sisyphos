// glad must be included before any other GL/GLFW headers.
#include <glad/glad.h>

#include <spdlog/spdlog.h>

#include "window.hpp"

int main()
{
#ifdef NDEBUG
    spdlog::set_level(spdlog::level::info);
#else
    spdlog::set_level(spdlog::level::debug);
#endif

    sisyphos::Window window{1280, 720, "Sisyphos"};

    while (!window.shouldClose())
    {
        window.pollEvents();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        window.swapBuffers();
    }

    return 0;
}

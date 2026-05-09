// glad must be included before any other GL/GLFW headers.
#include <glad/glad.h>

#include "window.hpp"

int main()
{
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

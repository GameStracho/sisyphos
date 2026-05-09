// glad must be included before GLFW so it can define the GL function pointers
// that GLFW would otherwise leave undefined.
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>

#include "window.hpp"

#include <stdexcept>
#include <string>

namespace sisyphos {

namespace {

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    spdlog::debug("Framebuffer resized: {}x{}", width, height);
}

} // namespace

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
Window::Window(int width, int height, std::string_view title, bool fullscreen)
    : m_width(width), m_height(height), m_isFullscreen(fullscreen)
{
    spdlog::debug("Initializing GLFW...");

    if (!glfwInit())
    {
        spdlog::error("Failed to initialize GLFW");
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    spdlog::debug("GLFW window hints set: OpenGL 4.5 Core");

    GLFWmonitor* monitor = nullptr;
    if (fullscreen)
    {
        monitor = glfwGetPrimaryMonitor();

        if (!monitor)
        {
            spdlog::error("Failed to get primary monitor for fullscreen mode");
            glfwTerminate();
            throw std::runtime_error("Failed to get primary monitor");
        }

        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        if (!mode)
        {
            spdlog::error("Failed to get primary monitor's video mode");
            glfwTerminate();
            throw std::runtime_error("Failed to get primary monitor's video mode");
        }

        m_width  = mode->width;
        m_height = mode->height;
        spdlog::debug("Fullscreen mode: native resolution {}x{}", m_width, m_height);
    }

    spdlog::debug("Creating GLFW window \"{}\" ({}x{}, fullscreen={})",
                  title, m_width, m_height, fullscreen);

    m_handle = glfwCreateWindow(m_width, m_height, std::string(title).c_str(), monitor, nullptr);

    if (!m_handle)
    {
        spdlog::error("Failed to create GLFW window");
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(m_handle);
    spdlog::debug("OpenGL context made current");

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        spdlog::error("Failed to initialize GLAD");
        glfwDestroyWindow(m_handle);
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }

    spdlog::debug("GLAD initialized — OpenGL {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    glfwSetFramebufferSizeCallback(m_handle, framebufferSizeCallback);
    glViewport(0, 0, m_width, m_height);

    // Save initial windowed geometry so toggleFullscreen() can restore it.
    if (!fullscreen)
    {
        m_windowedWidth  = m_width;
        m_windowedHeight = m_height;
        glfwGetWindowPos(m_handle, &m_windowedX, &m_windowedY);
    }

    spdlog::debug("Window \"{}\" ready", title);
}

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
Window::~Window()
{
    if (m_handle)
    {
        glfwDestroyWindow(m_handle);
        spdlog::debug("GLFW window destroyed");
    }

    glfwTerminate();
    spdlog::debug("GLFW terminated");
}

// ---------------------------------------------------------------------------
// Move semantics
// ---------------------------------------------------------------------------
Window::Window(Window&& other) noexcept
    : m_handle(other.m_handle)
    , m_width(other.m_width)
    , m_height(other.m_height)
    , m_isFullscreen(other.m_isFullscreen)
    , m_windowedX(other.m_windowedX)
    , m_windowedY(other.m_windowedY)
    , m_windowedWidth(other.m_windowedWidth)
    , m_windowedHeight(other.m_windowedHeight)
{
    other.m_handle = nullptr;
}

Window& Window::operator=(Window&& other) noexcept
{
    if (this != &other)
    {
        if (m_handle)
            glfwDestroyWindow(m_handle);

        m_handle         = other.m_handle;
        m_width          = other.m_width;
        m_height         = other.m_height;
        m_isFullscreen   = other.m_isFullscreen;
        m_windowedX      = other.m_windowedX;
        m_windowedY      = other.m_windowedY;
        m_windowedWidth  = other.m_windowedWidth;
        m_windowedHeight = other.m_windowedHeight;
        other.m_handle   = nullptr;
    }

    return *this;
}

// ---------------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------------

bool Window::shouldClose() const
{
    return static_cast<bool>(glfwWindowShouldClose(m_handle));
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::swapBuffers()
{
    glfwSwapBuffers(m_handle);
}

void Window::toggleFullscreen()
{
    if (m_isFullscreen)
    {
        // Restore saved windowed position and size.
        glfwSetWindowMonitor(m_handle, nullptr,
                             m_windowedX, m_windowedY,
                             m_windowedWidth, m_windowedHeight, 0);
        m_width        = m_windowedWidth;
        m_height       = m_windowedHeight;
        m_isFullscreen = false;

        spdlog::debug("Window switched to windowed mode ({}x{})", m_width, m_height);
        return;
    }

    // Save current windowed geometry before going fullscreen.
    glfwGetWindowPos(m_handle, &m_windowedX, &m_windowedY);
    glfwGetWindowSize(m_handle, &m_windowedWidth, &m_windowedHeight);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    if (!monitor)
    {
        spdlog::error("Failed to get primary monitor for fullscreen toggle");
        return;
    }

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    if (!mode)
    {
        spdlog::error("Failed to get primary monitor's video mode for fullscreen toggle");
        return;
    }

    glfwSetWindowMonitor(m_handle, monitor, 0, 0,
                            mode->width, mode->height, mode->refreshRate);
    m_width        = mode->width;
    m_height       = mode->height;
    m_isFullscreen = true;

    spdlog::debug("Window switched to fullscreen mode ({}x{})", m_width, m_height);
}

} // namespace sisyphos

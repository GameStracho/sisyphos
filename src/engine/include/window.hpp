#pragma once

#include <string_view>

// Forward-declare GLFW handle to avoid leaking GLFW headers into consumers.
struct GLFWwindow;

namespace sisyphos
{

    class Window
    {
    public:
        /// Creates a GLFW window with an OpenGL 4.5 Core context.
        /// Throws std::runtime_error if GLFW or GLAD initialization fails.
        /// @param width      Initial window width in pixels (ignored in fullscreen — native resolution is used).
        /// @param height     Initial window height in pixels (ignored in fullscreen — native resolution is used).
        /// @param title      Window title bar text.
        /// @param fullscreen If true, opens on the primary monitor at its native resolution.
        Window(int width, int height, std::string_view title, bool fullscreen = false);
        ~Window();

        // Non-copyable
        Window(const Window &) = delete;
        Window &operator=(const Window &) = delete;

        // Movable
        Window(Window &&) noexcept;
        Window &operator=(Window &&) noexcept;

        /// Returns true when the OS or user has requested the window to close
        /// (e.g. the user clicked the × button). Use as the game-loop condition.
        [[nodiscard]] bool shouldClose() const;

        /// Processes all pending OS/window events (keyboard, mouse, resize, close
        /// button). Non-blocking — returns immediately if there are no events.
        /// Must be called once per frame.
        void pollEvents();

        /// Swaps the front and back buffers, displaying the rendered frame on screen.
        void swapBuffers();

        /// Toggles between windowed and fullscreen mode. In fullscreen the window
        /// covers the primary monitor at its native resolution. The previous windowed
        /// size and position are restored when switching back.
        void toggleFullscreen();

        /// Returns the current framebuffer width in pixels.
        [[nodiscard]] int getWidth() const { return m_width; }

        /// Returns the current framebuffer height in pixels.
        [[nodiscard]] int getHeight() const { return m_height; }

        /// Returns the raw GLFWwindow pointer. Use when passing the window to other
        /// subsystems (input, ImGui, RmlUi) that require direct GLFW access.
        [[nodiscard]] GLFWwindow *getHandle() const { return m_handle; }

    private:
        GLFWwindow *m_handle = nullptr;
        int m_width = 0;
        int m_height = 0;
        bool m_isFullscreen = false;

        // Saved windowed geometry — restored when leaving fullscreen.
        int m_windowedX = 0;
        int m_windowedY = 0;
        int m_windowedWidth = 0;
        int m_windowedHeight = 0;
    };

} // namespace sisyphos

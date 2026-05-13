#pragma once

#include <glad/glad.h>

#include "opengl/enums.hpp"

namespace sisyphos::opengl
{

// Forward declarations so consumers of framebuffer.hpp don't have to include
// texture.hpp / renderbuffer.hpp directly.
class Texture;
class RenderBuffer;

class Framebuffer
{
public:
    /// Creates and allocates an OpenGL framebuffer object.
    /// @param width   Width of the framebuffer in pixels.
    /// @param height  Height of the framebuffer in pixels.
    Framebuffer(int width, int height);
    ~Framebuffer();

    Framebuffer(const Framebuffer&) = delete;
    Framebuffer& operator=(const Framebuffer&) = delete;

    Framebuffer(Framebuffer&& other) noexcept;
    Framebuffer& operator=(Framebuffer&& other) noexcept;

    /// Binds this framebuffer as the active draw/read target.
    void bind() const;

    /// Unbinds this framebuffer, restoring the default framebuffer (FBO 0).
    void unbind() const;

    /// Attaches a texture as a color, depth, or stencil attachment.
    /// @param attachment  The attachment point to bind to.
    /// @param texture     The texture to attach.
    void attachTexture(FramebufferAttachment attachment, const Texture& texture);

    /// Attaches a renderbuffer as a colour, depth, or stencil attachment.
    /// @param attachment   The attachment point to bind to.
    /// @param renderBuffer The renderbuffer to attach.
    void attachRenderBuffer(FramebufferAttachment attachment, const RenderBuffer& renderBuffer);

    /// Returns true when the FBO is complete; logs an error and returns false otherwise.
    [[nodiscard]] bool isComplete() const;

    /// Returns the underlying OpenGL framebuffer object ID.
    [[nodiscard]] GLuint getId() const { return m_id; }

    /// Returns the framebuffer width in pixels.
    [[nodiscard]] int getWidth() const { return m_width; }

    /// Returns the framebuffer height in pixels.
    [[nodiscard]] int getHeight() const { return m_height; }

private:
    GLuint m_id = 0;
    int m_width = 0;
    int m_height = 0;
};

} // namespace sisyphos::opengl

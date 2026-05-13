#pragma once

#include <glad/glad.h>

#include "opengl/enums.hpp"

namespace sisyphos::opengl
{

class RenderBuffer
{
public:
    /// Creates and allocates a renderbuffer with the given format and dimensions.
    /// @param format  Internal storage format.
    /// @param width   Width in pixels.
    /// @param height  Height in pixels.
    RenderBuffer(ERenderbufferFormat format, int width, int height);
    ~RenderBuffer();

    RenderBuffer(const RenderBuffer&) = delete;
    RenderBuffer& operator=(const RenderBuffer&) = delete;

    RenderBuffer(RenderBuffer&& other) noexcept;
    RenderBuffer& operator=(RenderBuffer&& other) noexcept;

    /// Binds this renderbuffer as the active GL_RENDERBUFFER target.
    void bind() const;

    /// Unbinds the currently bound renderbuffer (binds 0).
    void unbind() const;

    /// Reallocates the renderbuffer storage at the new dimensions.
    /// @param width   New width in pixels.
    /// @param height  New height in pixels.
    void resize(int width, int height);

    /// Returns the underlying OpenGL renderbuffer object ID.
    [[nodiscard]] GLuint getId() const { return m_id; }

    /// Returns the current width in pixels.
    [[nodiscard]] int getWidth() const { return m_width; }

    /// Returns the current height in pixels.
    [[nodiscard]] int getHeight() const { return m_height; }

private:
    GLuint m_id = 0;
    ERenderbufferFormat m_format = ERenderbufferFormat::Depth24Stencil8;
    int m_width = 0;
    int m_height = 0;
};

} // namespace sisyphos::opengl

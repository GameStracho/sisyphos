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
    Framebuffer(int width, int height);
    ~Framebuffer();

    Framebuffer(const Framebuffer&)            = delete;
    Framebuffer& operator=(const Framebuffer&) = delete;

    Framebuffer(Framebuffer&& other) noexcept;
    Framebuffer& operator=(Framebuffer&& other) noexcept;

    void bind()   const;
    void unbind() const; // rebinds default FBO 0

    void attachTexture(FramebufferAttachment attachment, const Texture& texture);
    void attachRenderBuffer(FramebufferAttachment attachment, const RenderBuffer& renderBuffer);

    /// Returns true when the FBO is complete; logs an error and returns false otherwise.
    [[nodiscard]] bool isComplete() const;

    [[nodiscard]] GLuint getId()     const { return m_id;     }
    [[nodiscard]] int    getWidth()  const { return m_width;  }
    [[nodiscard]] int    getHeight() const { return m_height; }

private:
    GLuint m_id     = 0;
    int    m_width  = 0;
    int    m_height = 0;
};

} // namespace sisyphos::opengl

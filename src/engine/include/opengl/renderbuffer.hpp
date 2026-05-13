#pragma once

#include <glad/glad.h>

#include "opengl/enums.hpp"

namespace sisyphos::opengl
{

class RenderBuffer
{
public:
    RenderBuffer(RenderbufferFormat format, int width, int height);
    ~RenderBuffer();

    RenderBuffer(const RenderBuffer&)            = delete;
    RenderBuffer& operator=(const RenderBuffer&) = delete;

    RenderBuffer(RenderBuffer&& other) noexcept;
    RenderBuffer& operator=(RenderBuffer&& other) noexcept;

    void bind()   const;
    void unbind() const;

    void resize(int width, int height);

    [[nodiscard]] GLuint getId()     const { return m_id;     }
    [[nodiscard]] int    getWidth()  const { return m_width;  }
    [[nodiscard]] int    getHeight() const { return m_height; }

private:
    GLuint             m_id     = 0;
    RenderbufferFormat m_format = RenderbufferFormat::Depth24Stencil8;
    int                m_width  = 0;
    int                m_height = 0;
};

} // namespace sisyphos::opengl

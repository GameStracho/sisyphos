#include "opengl/renderbuffer.hpp"
#include <spdlog/spdlog.h>

namespace sisyphos::opengl
{

RenderBuffer::RenderBuffer(ERenderbufferFormat format, int width, int height)
    : m_format(format), m_width(width), m_height(height)
{
    glGenRenderbuffers(1, &m_id);
    glNamedRenderbufferStorage(m_id, static_cast<GLenum>(m_format), m_width, m_height);
    spdlog::debug("RenderBuffer {} created ({}x{})", m_id, m_width, m_height);
}

RenderBuffer::~RenderBuffer()
{
    if (m_id)
    {
        glDeleteRenderbuffers(1, &m_id);
        spdlog::debug("RenderBuffer {} destroyed", m_id);
    }
}

RenderBuffer::RenderBuffer(RenderBuffer&& other) noexcept
    : m_id(other.m_id), m_format(other.m_format),
      m_width(other.m_width), m_height(other.m_height)
{
    other.m_id = 0;
}

RenderBuffer& RenderBuffer::operator=(RenderBuffer&& other) noexcept
{
    if (this != &other)
    {
        if (m_id) glDeleteRenderbuffers(1, &m_id);
        m_id       = other.m_id;
        m_format   = other.m_format;
        m_width    = other.m_width;
        m_height   = other.m_height;
        other.m_id = 0;
    }
    return *this;
}

void RenderBuffer::bind() const
{
    glBindRenderbuffer(GL_RENDERBUFFER, m_id);
}

void RenderBuffer::unbind() const
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RenderBuffer::resize(int width, int height)
{
    m_width  = width;
    m_height = height;

    glNamedRenderbufferStorage(m_id, static_cast<GLenum>(m_format), m_width, m_height);
    spdlog::debug("RenderBuffer {} resized to {}x{}", m_id, m_width, m_height);
}

} // namespace sisyphos::opengl

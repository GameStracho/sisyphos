#include "opengl/framebuffer.hpp"
#include "opengl/texture.hpp"
#include "opengl/renderbuffer.hpp"
#include <spdlog/spdlog.h>

namespace sisyphos::opengl
{

Framebuffer::Framebuffer(int width, int height)
    : m_width(width), m_height(height)
{
    glGenFramebuffers(1, &m_id);
    spdlog::debug("Framebuffer {} created ({}x{})", m_id, m_width, m_height);
}

Framebuffer::~Framebuffer()
{
    if (m_id)
    {
        glDeleteFramebuffers(1, &m_id);
        spdlog::debug("Framebuffer {} destroyed", m_id);
    }
}

Framebuffer::Framebuffer(Framebuffer&& other) noexcept
    : m_id(other.m_id), m_width(other.m_width), m_height(other.m_height)
{
    other.m_id = 0;
}

Framebuffer& Framebuffer::operator=(Framebuffer&& other) noexcept
{
    if (this != &other)
    {
        if (m_id)
            glDeleteFramebuffers(1, &m_id);
        
        m_id       = other.m_id;
        m_width    = other.m_width;
        m_height   = other.m_height;
        other.m_id = 0;
    }

    return *this;
}

void Framebuffer::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void Framebuffer::unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::attachTexture(FramebufferAttachment attachment, const Texture& texture)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           static_cast<GLenum>(attachment),
                           GL_TEXTURE_2D,
                           texture.getId(),
                           0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::attachRenderBuffer(FramebufferAttachment attachment, const RenderBuffer& renderBuffer)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                              static_cast<GLenum>(attachment),
                              GL_RENDERBUFFER,
                              renderBuffer.getId());
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

bool Framebuffer::isComplete() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    const GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        spdlog::error("Framebuffer {} is incomplete (status=0x{:x})", m_id, status);
        return false;
    }

    return true;
}

} // namespace sisyphos::opengl

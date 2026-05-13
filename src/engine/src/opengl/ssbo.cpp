#include "opengl/ssbo.hpp"
#include <spdlog/spdlog.h>

namespace sisyphos::opengl
{

SSBO::SSBO(GLsizeiptr size, BufferUsage usage)
{
    glGenBuffers(1, &m_id);
    glNamedBufferData(m_id, size, nullptr, static_cast<GLenum>(usage));
    spdlog::debug("SSBO {} created ({} bytes)", m_id, size);
}

SSBO::~SSBO()
{
    if (m_id)
    {
        glDeleteBuffers(1, &m_id);
        spdlog::debug("SSBO {} destroyed", m_id);
    }
}

SSBO::SSBO(SSBO&& other) noexcept : m_id(other.m_id)
{
    other.m_id = 0;
}

SSBO& SSBO::operator=(SSBO&& other) noexcept
{
    if (this != &other)
    {
        if (m_id)
            glDeleteBuffers(1, &m_id);
        
        m_id       = other.m_id;
        other.m_id = 0;
    }
    return *this;
}

void SSBO::bind() const
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
}

void SSBO::unbind() const
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void SSBO::bindBase(GLuint bindingPoint) const
{
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, m_id);
}

void SSBO::upload(const void* data, GLsizeiptr size, GLintptr offset) const
{
    glNamedBufferSubData(m_id, offset, size, data);
}

} // namespace sisyphos::opengl

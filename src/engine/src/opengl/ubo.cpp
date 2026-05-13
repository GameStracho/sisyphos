#include "opengl/ubo.hpp"
#include <spdlog/spdlog.h>

namespace sisyphos::opengl
{

UBO::UBO(GLsizeiptr size, BufferUsage usage)
{
    glGenBuffers(1, &m_id);

    glBindBuffer(GL_UNIFORM_BUFFER, m_id);
    glBufferData(GL_UNIFORM_BUFFER, size, nullptr, static_cast<GLenum>(usage));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    spdlog::debug("UBO {} created ({} bytes)", m_id, size);
}

UBO::~UBO()
{
    if (m_id)
    {
        glDeleteBuffers(1, &m_id);
        spdlog::debug("UBO {} destroyed", m_id);
    }
}

UBO::UBO(UBO&& other) noexcept : m_id(other.m_id)
{
    other.m_id = 0;
}

UBO& UBO::operator=(UBO&& other) noexcept
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

void UBO::bind() const
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_id);
}

void UBO::unbind() const
{
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UBO::bindBase(GLuint bindingPoint) const
{
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, m_id);
}

void UBO::upload(const void* data, GLsizeiptr size, GLintptr offset) const
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_id);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

} // namespace sisyphos::opengl

#include "opengl/vbo.hpp"
#include <spdlog/spdlog.h>

namespace sisyphos::opengl
{

VBO::VBO()
{
    glGenBuffers(1, &m_id);
    spdlog::debug("VBO {} created", m_id);
}

VBO::~VBO()
{
    if (m_id)
    {
        glDeleteBuffers(1, &m_id);
        spdlog::debug("VBO {} destroyed", m_id);
    }
}

VBO::VBO(VBO&& other) noexcept : m_id(other.m_id)
{
    other.m_id = 0;
}

VBO& VBO::operator=(VBO&& other) noexcept
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

void VBO::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VBO::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::upload(const void* data, GLsizeiptr size, EBufferUsage usage)
{
    glNamedBufferData(m_id, size, data, static_cast<GLenum>(usage));
    spdlog::debug("VBO {} uploaded {} bytes", m_id, size);
}

} // namespace sisyphos::opengl

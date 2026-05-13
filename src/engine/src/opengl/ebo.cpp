#include "opengl/ebo.hpp"
#include <spdlog/spdlog.h>

namespace sisyphos::opengl {

EBO::EBO()
{
    glGenBuffers(1, &m_id);
    spdlog::debug("EBO {} created", m_id);
}

EBO::~EBO()
{
    if (m_id)
    {
        glDeleteBuffers(1, &m_id);
        spdlog::debug("EBO {} destroyed", m_id);
    }
}

EBO::EBO(EBO&& other) noexcept : m_id(other.m_id)
{
    other.m_id = 0;
}

EBO& EBO::operator=(EBO&& other) noexcept
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

void EBO::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void EBO::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::upload(const void* data, GLsizeiptr size, BufferUsage usage)
{
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, static_cast<GLenum>(usage));
    spdlog::debug("EBO {} uploaded {} bytes", m_id, size);
}

} // namespace sisyphos::opengl

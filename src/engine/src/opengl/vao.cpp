#include "opengl/vao.hpp"
#include <spdlog/spdlog.h>

namespace sisyphos::opengl {

VAO::VAO()
{
    glGenVertexArrays(1, &m_id);
    spdlog::debug("VAO {} created", m_id);
}

VAO::~VAO()
{
    if (m_id)
    {
        glDeleteVertexArrays(1, &m_id);
        spdlog::debug("VAO {} destroyed", m_id);
    }
}

VAO::VAO(VAO&& other) noexcept : m_id(other.m_id)
{
    other.m_id = 0;
}

VAO& VAO::operator=(VAO&& other) noexcept
{
    if (this != &other)
    {
        if (m_id)
            glDeleteVertexArrays(1, &m_id);
        
        m_id       = other.m_id;
        other.m_id = 0;
    }
    return *this;
}

void VAO::bind() const
{
    glBindVertexArray(m_id);
}

void VAO::unbind() const
{
    glBindVertexArray(0);
}

void VAO::setAttribPointer(GLuint index, GLint size, AttribType type,
    bool normalized, GLsizei stride, const void* offset)
{
    glVertexAttribPointer(index, size, static_cast<GLenum>(type), normalized ? GL_TRUE : GL_FALSE, stride, offset);
}

void VAO::enableAttrib(GLuint index)
{
    glEnableVertexAttribArray(index);
}

} // namespace sisyphos::opengl

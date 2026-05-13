#include "opengl/shaderprogram.hpp"
#include <spdlog/spdlog.h>

#include <stdexcept>
#include <string>

#include <glm/gtc/type_ptr.hpp>

namespace sisyphos::opengl {

ShaderProgram::ShaderProgram(std::initializer_list<GLuint> shaderIds)
{
    m_id = glCreateProgram();
    spdlog::debug("ShaderProgram {} created, attaching {} shader(s)", m_id, shaderIds.size());

    for (GLuint id : shaderIds)
        glAttachShader(m_id, id);

    glLinkProgram(m_id);

    // Detach shaders immediately — the program owns the linked binary from
    // here on, and the Shader objects can be safely destroyed.
    for (GLuint id : shaderIds)
        glDetachShader(m_id, id);

    GLint success = 0;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);

    if (!success)
    {
        GLchar infoLog[1024];
        glGetProgramInfoLog(m_id, sizeof(infoLog), nullptr, infoLog);
        spdlog::error("ShaderProgram {} link failed: {}", m_id, infoLog);

        glDeleteProgram(m_id);
        m_id = 0;
        throw std::runtime_error("ShaderProgram link failed: " + std::string(infoLog));
    }

    spdlog::debug("ShaderProgram {} linked successfully", m_id);
}

ShaderProgram::~ShaderProgram()
{
    if (m_id)
    {
        glDeleteProgram(m_id);
        spdlog::debug("ShaderProgram {} destroyed", m_id);
    }
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept : m_id(other.m_id)
{
    other.m_id = 0;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
{
    if (this != &other)
    {
        if (m_id)
            glDeleteProgram(m_id);
        
        m_id       = other.m_id;
        other.m_id = 0;
    }
    return *this;
}

void ShaderProgram::use() const
{
    glUseProgram(m_id);
}

GLint ShaderProgram::getUniformLocation(std::string_view name) const
{
    return glGetUniformLocation(m_id, name.data());
}

// ---------------------------------------------------------------------------
// Uniform specialisations
// ---------------------------------------------------------------------------

template<> void ShaderProgram::set<int>(GLint location, int value)
{
    glUniform1i(location, value);
}

template<> void ShaderProgram::set<float>(GLint location, float value)
{
    glUniform1f(location, value);
}

template<> void ShaderProgram::set<glm::vec2>(GLint location, glm::vec2 value)
{
    glUniform2fv(location, 1, glm::value_ptr(value));
}

template<> void ShaderProgram::set<glm::vec3>(GLint location, glm::vec3 value)
{
    glUniform3fv(location, 1, glm::value_ptr(value));
}

template<> void ShaderProgram::set<glm::vec4>(GLint location, glm::vec4 value)
{
    glUniform4fv(location, 1, glm::value_ptr(value));
}

template<> void ShaderProgram::set<glm::mat3>(GLint location, glm::mat3 value)
{
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

template<> void ShaderProgram::set<glm::mat4>(GLint location, glm::mat4 value)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

} // namespace sisyphos::opengl

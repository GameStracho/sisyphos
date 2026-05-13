#include "opengl/shader.hpp"
#include <spdlog/spdlog.h>

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace sisyphos::opengl
{

namespace
{

std::string loadFile(const std::filesystem::path& path)
{
    std::ifstream file(path);

    if (!file.is_open())
        throw std::runtime_error("Failed to open shader file: " + path.string());

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

} // namespace

Shader::Shader(EShaderStage stage, const std::filesystem::path& sourcePath)
{
    spdlog::debug("Compiling shader: {}", sourcePath.string());

    const std::string source = loadFile(sourcePath);
    const char*       src    = source.c_str();

    m_id = glCreateShader(static_cast<GLenum>(stage));
    glShaderSource(m_id, 1, &src, nullptr);
    glCompileShader(m_id);

    GLint success = 0;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        GLchar infoLog[1024];
        glGetShaderInfoLog(m_id, sizeof(infoLog), nullptr, infoLog);
        spdlog::error("Shader compilation failed ({}): {}", sourcePath.string(), infoLog);

        glDeleteShader(m_id);
        m_id = 0;
        throw std::runtime_error("Shader compilation failed: " + std::string(infoLog));
    }

    spdlog::debug("Shader {} compiled (id={})", sourcePath.string(), m_id);
}

Shader::~Shader()
{
    if (m_id)
    {
        glDeleteShader(m_id);
        spdlog::debug("Shader {} deleted", m_id);
    }
}

Shader::Shader(Shader&& other) noexcept : m_id(other.m_id)
{
    other.m_id = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept
{
    if (this != &other)
    {
        if (m_id)
            glDeleteShader(m_id);

        m_id       = other.m_id;
        other.m_id = 0;
    }
    return *this;
}

} // namespace sisyphos::opengl

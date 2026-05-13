#pragma once

#include <initializer_list>
#include <string_view>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace sisyphos::opengl
{

/// A linked OpenGL shader program built from one or more compiled Shader
/// stages.  Throws std::runtime_error if linking fails.
class ShaderProgram
{
public:
    /// Links the program from a list of compiled shader IDs.
    /// Typical usage: ShaderProgram prog{vert.getId(), frag.getId()};
    /// @param shaderIds  List of compiled Shader object IDs to attach and link.
    explicit ShaderProgram(std::initializer_list<GLuint> shaderIds);
    ~ShaderProgram();

    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;

    ShaderProgram(ShaderProgram&&) noexcept;
    ShaderProgram& operator=(ShaderProgram&&) noexcept;

    /// Installs this program as the active shader program for subsequent draw calls.
    void use() const;

    /// Looks up a uniform location by name.  Returns -1 if not found.
    [[nodiscard]] GLint getUniformLocation(std::string_view name) const;

    /// Returns the underlying OpenGL program object ID.
    [[nodiscard]] GLuint getId() const { return m_id; }

    // -----------------------------------------------------------------------
    // Uniform setters
    //
    // Two overloads per type:
    //   set<T>(GLint location, T)        — fast path, no string lookup
    //   set<T>(std::string_view name, T) — convenience, calls getUniformLocation
    //
    // The primary template is = delete so passing an unsupported type is a
    // compile error rather than a silent runtime failure.
    // -----------------------------------------------------------------------

    template<typename T>
    void set(GLint location, T value) = delete;

    /// Convenience overload that looks up the uniform by name before setting.
    /// @param name   Name of the uniform variable in the shader source.
    /// @param value  Value to assign to the uniform.
    template<typename T>
    void set(std::string_view name, T value) { set<T>(getUniformLocation(name), value); }

private:
    GLuint m_id = 0;
};

// Explicit specialisation declarations — definitions live in shaderprogram.cpp
// so that glm headers are only compiled once.
template<> void ShaderProgram::set<int>(GLint location, int value);
template<> void ShaderProgram::set<float>(GLint location, float value);
template<> void ShaderProgram::set<glm::vec2>(GLint location, glm::vec2 value);
template<> void ShaderProgram::set<glm::vec3>(GLint location, glm::vec3 value);
template<> void ShaderProgram::set<glm::vec4>(GLint location, glm::vec4 value);
template<> void ShaderProgram::set<glm::mat3>(GLint location, glm::mat3 value);
template<> void ShaderProgram::set<glm::mat4>(GLint location, glm::mat4 value);

} // namespace sisyphos::opengl

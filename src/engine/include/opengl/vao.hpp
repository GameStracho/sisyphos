#pragma once

#include <glad/glad.h>

namespace sisyphos::opengl {

class VAO
{
public:
    VAO();
    ~VAO();

    VAO(const VAO&)            = delete;
    VAO& operator=(const VAO&) = delete;

    VAO(VAO&&) noexcept;
    VAO& operator=(VAO&&) noexcept;

    void bind() const;
    void unbind() const;

    /// Define how a vertex attribute reads from the currently bound VBO.
    /// @param index      Attribute location (matches layout(location = N) in GLSL).
    /// @param size       Number of components (1–4).
    /// @param type       Component type (e.g. GL_FLOAT).
    /// @param normalized Whether fixed-point values should be normalised.
    /// @param stride     Byte offset between consecutive vertices (0 = tightly packed).
    /// @param offset     Byte offset of the first component within a vertex.
    void setAttribPointer(GLuint index, GLint size, GLenum type,
                          GLboolean normalized, GLsizei stride,
                          const void* offset);

    /// Enable a vertex attribute.
    /// @param index      Attribute location (matches layout(location = N) in GLSL).
    void enableAttrib(GLuint index);

    [[nodiscard]] GLuint getId() const { return m_id; }

private:
    GLuint m_id = 0;
};

} // namespace sisyphos::opengl

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

    /// Defines how a vertex attribute reads from the currently bound VBO.
    /// Must be called while this VAO and the source VBO are both bound.
    /// @param index      Attribute location (matches layout(location = N) in GLSL).
    /// @param size       Number of components per vertex (1–4).
    /// @param type       Component data type.
    /// @param normalized Whether fixed-point values should be normalised to [0,1] or [-1,1].
    /// @param stride     Byte distance between consecutive vertices (0 = tightly packed).
    /// @param offset     Byte offset of the first component within a single vertex.
    void setAttribPointer(GLuint index, GLint size, AttribType type,
        bool normalized, GLsizei stride, const void* offset);

    /// Enable a vertex attribute.
    /// @param index      Attribute location (matches layout(location = N) in GLSL).
    void enableAttrib(GLuint index);

    [[nodiscard]] GLuint getId() const { return m_id; }

private:
    GLuint m_id = 0;
};

} // namespace sisyphos::opengl

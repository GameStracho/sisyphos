#pragma once

#include <glad/glad.h>
#include "enums.hpp"

namespace sisyphos::opengl
{

class EBO
{
public:
    /// Creates and allocates an OpenGL element array buffer object.
    EBO();
    ~EBO();

    EBO(const EBO&) = delete;
    EBO& operator=(const EBO&) = delete;

    EBO(EBO&&) noexcept;
    EBO& operator=(EBO&&) noexcept;

    /// Binds this EBO as the active GL_ELEMENT_ARRAY_BUFFER.
    void bind() const;

    /// Unbinds the currently bound element array buffer (binds 0).
    void unbind() const;

    /// Uploads index data to GPU memory, replacing any previously stored data.
    /// @param data  Pointer to the raw index data.
    /// @param size  Size in bytes of the data.
    /// @param usage GPU access hint (default: StaticDraw).
    void upload(const void* data, GLsizeiptr size,
        BufferUsage usage = BufferUsage::StaticDraw);

    /// Returns the underlying OpenGL object ID.
    [[nodiscard]] GLuint getId() const { return m_id; }

private:
    GLuint m_id = 0;
};

} // namespace sisyphos::opengl

#pragma once

#include <glad/glad.h>
#include "enums.hpp"

namespace sisyphos::opengl
{

class VBO
{
public:
    /// Creates and allocates an OpenGL array buffer object.
    VBO();
    ~VBO();

    VBO(const VBO&) = delete;
    VBO& operator=(const VBO&) = delete;

    VBO(VBO&&) noexcept;
    VBO& operator=(VBO&&) noexcept;

    /// Binds this VBO as the active GL_ARRAY_BUFFER.
    void bind() const;

    /// Unbinds the currently bound array buffer (binds 0).
    void unbind() const;

    /// Uploads vertex data to GPU memory, replacing any previously stored data.
    /// @param data  Pointer to the raw vertex data.
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

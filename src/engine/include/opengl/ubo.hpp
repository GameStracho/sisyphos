#pragma once

#include <glad/glad.h>

#include "opengl/enums.hpp"

namespace sisyphos::opengl
{

class UBO
{
public:
    /// Allocates a GPU buffer of the given size.  The buffer is left
    /// uninitialised until the first call to upload().
    UBO(GLsizeiptr size, BufferUsage usage = BufferUsage::DynamicDraw);
    ~UBO();

    UBO(const UBO&) = delete;
    UBO& operator=(const UBO&) = delete;

    UBO(UBO&& other) noexcept;
    UBO& operator=(UBO&& other) noexcept;

    /// Binds this buffer as the active GL_UNIFORM_BUFFER target.
    void bind() const;

    /// Unbinds the currently bound uniform buffer (binds 0).
    void unbind() const;

    /// Binds this buffer to an indexed uniform-buffer binding point.
    /// @param bindingPoint  The binding index referenced by layout(binding = N) in GLSL.
    void bindBase(GLuint bindingPoint) const;

    /// Uploads data into the buffer at the given byte offset.
    /// @param data    Pointer to the data to upload.
    /// @param size    Number of bytes to upload.
    /// @param offset  Byte offset into the buffer to write at (default: 0).
    void upload(const void* data, GLsizeiptr size, GLintptr offset = 0) const;

    /// Returns the underlying OpenGL buffer object ID.
    [[nodiscard]] GLuint getId() const { return m_id; }

private:
    GLuint m_id = 0;
};

} // namespace sisyphos::opengl

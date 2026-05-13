#pragma once

#include <glad/glad.h>

#include "opengl/enums.hpp"

namespace sisyphos::opengl
{

class SSBO
{
public:
    /// Allocates a GPU buffer of the given size.  The buffer is left
    /// uninitialised until the first call to upload().
    SSBO(GLsizeiptr size, BufferUsage usage = BufferUsage::DynamicDraw);
    ~SSBO();

    SSBO(const SSBO&) = delete;
    SSBO& operator=(const SSBO&) = delete;

    SSBO(SSBO&& other) noexcept;
    SSBO& operator=(SSBO&& other) noexcept;

    /// Binds this buffer as the active GL_SHADER_STORAGE_BUFFER target.
    void bind() const;

    /// Unbinds the currently bound shader storage buffer (binds 0).
    void unbind() const;

    /// Binds this buffer to an indexed shader-storage binding point.
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

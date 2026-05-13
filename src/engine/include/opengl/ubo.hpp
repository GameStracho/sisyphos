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

    UBO(const UBO&)            = delete;
    UBO& operator=(const UBO&) = delete;

    UBO(UBO&& other) noexcept;
    UBO& operator=(UBO&& other) noexcept;

    void bind()   const;
    void unbind() const;

    /// Bind to the indexed uniform-buffer binding point.
    void bindBase(GLuint bindingPoint) const;

    /// Upload data into the buffer at the given byte offset.
    void upload(const void* data, GLsizeiptr size, GLintptr offset = 0) const;

    [[nodiscard]] GLuint getId() const { return m_id; }

private:
    GLuint m_id = 0;
};

} // namespace sisyphos::opengl

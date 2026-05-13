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

    SSBO(const SSBO&)            = delete;
    SSBO& operator=(const SSBO&) = delete;

    SSBO(SSBO&& other) noexcept;
    SSBO& operator=(SSBO&& other) noexcept;

    void bind()   const;
    void unbind() const;

    /// Bind to the indexed shader-storage binding point.
    void bindBase(GLuint bindingPoint) const;

    /// Upload data into the buffer at the given byte offset.
    void upload(const void* data, GLsizeiptr size, GLintptr offset = 0) const;

    [[nodiscard]] GLuint getId() const { return m_id; }

private:
    GLuint m_id = 0;
};

} // namespace sisyphos::opengl

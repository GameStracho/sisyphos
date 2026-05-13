#pragma once

#include <glad/glad.h>
#include "enums.hpp"

namespace sisyphos::opengl {

class VBO
{
public:
    VBO();
    ~VBO();

    VBO(const VBO&)            = delete;
    VBO& operator=(const VBO&) = delete;

    VBO(VBO&&) noexcept;
    VBO& operator=(VBO&&) noexcept;

    void bind() const;
    void unbind() const;

    /// Upload vertex data to the GPU.
    /// @param data  Pointer to the raw vertex data.
    /// @param size  Size in bytes of the data.
    /// @param usage GPU access hint (default: StaticDraw).
    void upload(const void* data, GLsizeiptr size,
                BufferUsage usage = BufferUsage::StaticDraw);

    [[nodiscard]] GLuint getId() const { return m_id; }

private:
    GLuint m_id = 0;
};

} // namespace sisyphos::opengl

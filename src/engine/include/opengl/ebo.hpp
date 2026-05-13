#pragma once

#include <glad/glad.h>
#include "enums.hpp"

namespace sisyphos::opengl {

class EBO
{
public:
    EBO();
    ~EBO();

    EBO(const EBO&)            = delete;
    EBO& operator=(const EBO&) = delete;

    EBO(EBO&&) noexcept;
    EBO& operator=(EBO&&) noexcept;

    void bind() const;
    void unbind() const;

    /// Upload index data to the GPU.
    /// @param data  Pointer to the raw index data.
    /// @param size  Size in bytes of the data.
    /// @param usage GPU access hint (default: StaticDraw).
    void upload(const void* data, GLsizeiptr size,
                BufferUsage usage = BufferUsage::StaticDraw);

    [[nodiscard]] GLuint getId() const { return m_id; }

private:
    GLuint m_id = 0;
};

} // namespace sisyphos::opengl

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "opengl/enums.hpp"

namespace sisyphos::opengl
{

/// Sets the color used when clearing the color buffer.
/// @param color color to clear.
inline void setClearColor(glm::vec4 color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

/// Clears the specified framebuffer buffers.
/// @param bits  One or more ClearBit flags combined with | indicating which buffers to clear.
inline void clear(ClearBit bits = ClearBit::Color)
{
    glClear(static_cast<GLbitfield>(bits));
}

/// Draws primitives from the currently bound VAO without an index buffer.
/// @param primitive  The type of primitive to render.
/// @param first      Index of the first vertex to draw.
/// @param count      Number of vertices to draw.
inline void drawArrays(PrimitiveType primitive, GLint first, GLsizei count)
{
    glDrawArrays(static_cast<GLenum>(primitive), first, count);
}

} // namespace sisyphos::opengl

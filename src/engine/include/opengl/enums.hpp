#pragma once

#include <glad/glad.h>

// All OpenGL enum classes use : GLenum as their underlying type so the GL
// constant values are baked in directly.  Internal code casts with
// static_cast<GLenum>(e), which is a zero-cost no-op at runtime.

namespace sisyphos::opengl
{

// ---------------------------------------------------------------------------
// Shader stage
// ---------------------------------------------------------------------------
enum class ShaderStage : GLenum
{
    Vertex = GL_VERTEX_SHADER,
    Fragment = GL_FRAGMENT_SHADER,
    Geometry = GL_GEOMETRY_SHADER,
    Compute = GL_COMPUTE_SHADER,
    TessControl = GL_TESS_CONTROL_SHADER,
    TessEvaluation = GL_TESS_EVALUATION_SHADER,
};

// ---------------------------------------------------------------------------
// Buffer usage hint
// ---------------------------------------------------------------------------
enum class BufferUsage : GLenum
{
    StaticDraw = GL_STATIC_DRAW,
    DynamicDraw = GL_DYNAMIC_DRAW,
    StreamDraw = GL_STREAM_DRAW,
};

// ---------------------------------------------------------------------------
// Texture target
// ---------------------------------------------------------------------------
enum class TextureTarget : GLenum
{
    Texture2D = GL_TEXTURE_2D,
    Texture3D = GL_TEXTURE_3D,
    CubeMap = GL_TEXTURE_CUBE_MAP,
    Texture2DArray = GL_TEXTURE_2D_ARRAY,
};

// ---------------------------------------------------------------------------
// Texture wrap mode
// ---------------------------------------------------------------------------
enum class TextureWrap : GLenum
{
    Repeat = GL_REPEAT,
    ClampToEdge = GL_CLAMP_TO_EDGE,
    MirroredRepeat = GL_MIRRORED_REPEAT,
};

// ---------------------------------------------------------------------------
// Texture filter mode
// ---------------------------------------------------------------------------
enum class TextureFilter : GLenum
{
    Nearest = GL_NEAREST,
    Linear = GL_LINEAR,
    NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
    LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR,
};

// ---------------------------------------------------------------------------
// Pixel format
// ---------------------------------------------------------------------------
enum class PixelFormat : GLenum
{
    R = GL_RED,
    RG = GL_RG,
    RGB = GL_RGB,
    RGBA = GL_RGBA,
    DepthComponent = GL_DEPTH_COMPONENT,
    DepthStencil = GL_DEPTH_STENCIL,
};

// ---------------------------------------------------------------------------
// Framebuffer attachment point
// ---------------------------------------------------------------------------
enum class FramebufferAttachment : GLenum
{
    Color0 = GL_COLOR_ATTACHMENT0,
    Color1 = GL_COLOR_ATTACHMENT1,
    Color2 = GL_COLOR_ATTACHMENT2,
    Color3 = GL_COLOR_ATTACHMENT3,
    Color4 = GL_COLOR_ATTACHMENT4,
    Color5 = GL_COLOR_ATTACHMENT5,
    Color6 = GL_COLOR_ATTACHMENT6,
    Color7 = GL_COLOR_ATTACHMENT7,
    Depth = GL_DEPTH_ATTACHMENT,
    Stencil = GL_STENCIL_ATTACHMENT,
    DepthStencil = GL_DEPTH_STENCIL_ATTACHMENT,
};

// ---------------------------------------------------------------------------
// Renderbuffer internal format
// ---------------------------------------------------------------------------
enum class RenderbufferFormat : GLenum
{
    Depth24Stencil8 = GL_DEPTH24_STENCIL8,
    Depth32F = GL_DEPTH_COMPONENT32F,
    DepthComponent24 = GL_DEPTH_COMPONENT24,
};

// ---------------------------------------------------------------------------
// Vertex attribute component type (used by VAO::setAttribPointer)
// ---------------------------------------------------------------------------
enum class AttribType : GLenum
{
    Byte = GL_BYTE,
    UnsignedByte = GL_UNSIGNED_BYTE,
    Short = GL_SHORT,
    UnsignedShort = GL_UNSIGNED_SHORT,
    Int = GL_INT,
    UnsignedInt = GL_UNSIGNED_INT,
    Float = GL_FLOAT,
    Double = GL_DOUBLE,
};

// ---------------------------------------------------------------------------
// Primitive type for draw calls
// ---------------------------------------------------------------------------
enum class PrimitiveType : GLenum
{
    Points = GL_POINTS,
    Lines = GL_LINES,
    LineStrip = GL_LINE_STRIP,
    LineLoop = GL_LINE_LOOP,
    Triangles = GL_TRIANGLES,
    TriangleStrip = GL_TRIANGLE_STRIP,
    TriangleFan = GL_TRIANGLE_FAN,
};

// ---------------------------------------------------------------------------
// Framebuffer clear mask — values can be combined with |
// ---------------------------------------------------------------------------
enum class ClearBit : GLbitfield
{
    Color = GL_COLOR_BUFFER_BIT,
    Depth = GL_DEPTH_BUFFER_BIT,
    Stencil = GL_STENCIL_BUFFER_BIT,
};

inline ClearBit operator|(ClearBit a, ClearBit b)
{
    return static_cast<ClearBit>(static_cast<GLbitfield>(a) | static_cast<GLbitfield>(b));
}

} // namespace sisyphos::opengl

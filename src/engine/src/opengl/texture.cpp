#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "opengl/texture.hpp"
#include <spdlog/spdlog.h>

#include <stdexcept>

namespace sisyphos::opengl {

Texture::Texture(
    const std::filesystem::path& path,
    TextureTarget                target,
    bool                         flipVertically)
    : m_target(target)
{
    spdlog::debug("Loading texture: {}", path.string());

    stbi_set_flip_vertically_on_load(flipVertically ? 1 : 0);

    int channels = 0;
    unsigned char* data = stbi_load(path.string().c_str(), &m_width, &m_height, &channels, 0);
    if (!data)
    {
        spdlog::error("Failed to load texture: {}", path.string());
        throw std::runtime_error("Failed to load texture: " + path.string());
    }

    GLenum internalFormat = GL_RGBA8;
    GLenum pixelFormat    = GL_RGBA;
    switch (channels)
    {
        case 1: internalFormat = GL_R8;    pixelFormat = GL_RED;  break;
        case 2: internalFormat = GL_RG8;   pixelFormat = GL_RG;   break;
        case 3: internalFormat = GL_RGB8;  pixelFormat = GL_RGB;  break;
        case 4: internalFormat = GL_RGBA8; pixelFormat = GL_RGBA; break;
        default:
            stbi_image_free(data);
            spdlog::error("Unsupported channel count {} in texture: {}", channels, path.string());
            throw std::runtime_error("Unsupported channel count in texture: " + path.string());
    }

    const GLenum target_gl = static_cast<GLenum>(m_target);

    glGenTextures(1, &m_id);
    glBindTexture(target_gl, m_id);

    glTexImage2D(target_gl, 0, internalFormat,
                 m_width, m_height, 0, pixelFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(target_gl);

    // Sensible defaults
    glTexParameteri(target_gl, GL_TEXTURE_WRAP_S,     GL_REPEAT);
    glTexParameteri(target_gl, GL_TEXTURE_WRAP_T,     GL_REPEAT);
    glTexParameteri(target_gl, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(target_gl, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(target_gl, 0);
    stbi_image_free(data);

    spdlog::debug("Texture {} loaded ({}x{}, {} channels, id={})",
                  path.string(), m_width, m_height, channels, m_id);
}

Texture::~Texture()
{
    if (m_id)
    {
        glDeleteTextures(1, &m_id);
        spdlog::debug("Texture {} destroyed", m_id);
    }
}

Texture::Texture(Texture&& other) noexcept
    : m_id(other.m_id), m_target(other.m_target),
      m_width(other.m_width), m_height(other.m_height)
{
    other.m_id = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept
{
    if (this != &other)
    {
        if (m_id)
            glDeleteTextures(1, &m_id);
        
        m_id       = other.m_id;
        m_target   = other.m_target;
        m_width    = other.m_width;
        m_height   = other.m_height;
        other.m_id = 0;
    }

    return *this;
}

void Texture::bind(GLuint unit) const
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(static_cast<GLenum>(m_target), m_id);
}

void Texture::unbind() const
{
    glBindTexture(static_cast<GLenum>(m_target), 0);
}

void Texture::setWrap(TextureWrap s, TextureWrap t) const
{
    const GLenum target = static_cast<GLenum>(m_target);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, static_cast<GLenum>(s));
    glTexParameteri(target, GL_TEXTURE_WRAP_T, static_cast<GLenum>(t));
}

void Texture::setFilter(TextureFilter min, TextureFilter mag) const
{
    const GLenum target = static_cast<GLenum>(m_target);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(min));
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(mag));
}

} // namespace sisyphos::opengl

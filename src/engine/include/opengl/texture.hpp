#pragma once

#include <glad/glad.h>

#include "opengl/enums.hpp"

#include <filesystem>

namespace sisyphos::opengl
{

class Texture
{
public:
    /// Loads an image from disk and uploads it as an OpenGL texture.
    /// @param path            Path to the image file (PNG, JPG, etc.).
    /// @param target          Texture target to bind to (default: Texture2D).
    /// @param flipVertically  Flip the image vertically on load (default: true,
    ///                        corrects for OpenGL's bottom-left origin).
    explicit Texture(
        const std::filesystem::path& path,
        ETextureTarget target = ETextureTarget::Texture2D,
        bool flipVertically = true);

    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    /// Activates the given texture unit and binds this texture to it.
    /// @param unit  Texture unit index (0-based, maps to GL_TEXTURE0 + unit).
    void bind(GLuint unit = 0) const;

    /// Unbinds the texture target (binds texture 0).
    void unbind() const;

    /// Sets the wrap mode for the S and T axes.
    /// @param s  Wrap mode for the horizontal (S / U) axis.
    /// @param t  Wrap mode for the vertical (T / V) axis.
    void setWrap(ETextureWrap s, ETextureWrap t) const;

    /// Sets the minification and magnification filter modes.
    /// @param min  Filter used when the texture is rendered smaller than its original size.
    /// @param mag  Filter used when the texture is rendered larger than its original size.
    void setFilter(ETextureFilter min, ETextureFilter mag) const;

    /// Returns the width of the texture in pixels.
    [[nodiscard]] int getWidth() const { return m_width; }

    /// Returns the height of the texture in pixels.
    [[nodiscard]] int getHeight() const { return m_height; }

    /// Returns the underlying OpenGL texture object ID.
    [[nodiscard]] GLuint getId() const { return m_id; }

private:
    GLuint m_id = 0;
    ETextureTarget m_target = ETextureTarget::Texture2D;
    int m_width = 0;
    int m_height = 0;
};

} // namespace sisyphos::opengl

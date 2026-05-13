#pragma once

#include <glad/glad.h>

#include "opengl/enums.hpp"

#include <filesystem>

namespace sisyphos::opengl {

class Texture
{
public:
    explicit Texture(
        const std::filesystem::path& path,
        TextureTarget                target          = TextureTarget::Texture2D,
        bool                         flipVertically  = true);

    ~Texture();

    Texture(const Texture&)            = delete;
    Texture& operator=(const Texture&) = delete;

    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    void bind(GLuint unit = 0) const;
    void unbind() const;

    void setWrap(TextureWrap s, TextureWrap t) const;
    void setFilter(TextureFilter min, TextureFilter mag) const;

    [[nodiscard]] int    getWidth()  const { return m_width;  }
    [[nodiscard]] int    getHeight() const { return m_height; }
    [[nodiscard]] GLuint getId()     const { return m_id;     }

private:
    GLuint        m_id     = 0;
    TextureTarget m_target = TextureTarget::Texture2D;
    int           m_width  = 0;
    int           m_height = 0;
};

} // namespace sisyphos::opengl

#pragma once

#include <filesystem>
#include <glad/glad.h>
#include "enums.hpp"

namespace sisyphos::opengl {

/// A single compiled shader stage.  Not used directly — pass getId() to
/// ShaderProgram.  Throws std::runtime_error on compile failure.
class Shader
{
public:
    Shader(ShaderStage stage, const std::filesystem::path& sourcePath);
    ~Shader();

    Shader(const Shader&)            = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&&) noexcept;
    Shader& operator=(Shader&&) noexcept;

    [[nodiscard]] GLuint getId() const { return m_id; }

private:
    GLuint m_id = 0;
};

} // namespace sisyphos::opengl

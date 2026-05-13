#version 450 core

in  vec2 vTexCoord;
out vec4 FragColor;

layout(location = 0) uniform sampler2D uTexture;

void main()
{
    FragColor = texture(uTexture, vTexCoord);
}

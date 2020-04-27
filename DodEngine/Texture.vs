#version 330 core
layout (location = 0) in vec4 inPosition;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec2 inTexturePosition;

out vec4 inputColor;
out vec2 texturePosition;

void main()
{
    gl_Position = inPosition;
    inputColor = inColor;
    texturePosition = inTexturePosition;
}
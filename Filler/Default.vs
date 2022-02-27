#version 330 core
layout (location = 0) in vec4 inPosition;
layout (location = 1) in vec4 inColor;

out vec4 inputColor;

void main()
{
    gl_Position = inPosition;
    inputColor = inColor;
}
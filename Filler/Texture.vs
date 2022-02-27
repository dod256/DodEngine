#version 330 core
layout (location = 0) in vec4 inPosition;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec2 inTexturePosition;

out vec4 inputColor;
out vec2 texturePosition;

uniform vec4 cameraPosition;

void main()
{
    gl_Position = vec4((inPosition.x - cameraPosition.x) / cameraPosition.z, (inPosition.y - cameraPosition.y) / cameraPosition.w, inPosition.z, inPosition.w);
    inputColor = inColor;
    texturePosition = inTexturePosition;
}
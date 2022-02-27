#version 330 core
out vec4 FragColor;
  
in vec4 inputColor;
in vec2 texturePosition;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, texturePosition);
}
#version 330 core
layout (location = 0) in vec2 center;
void main()
{
   gl_Position = vec4(center, 0.0, 1.0);
}
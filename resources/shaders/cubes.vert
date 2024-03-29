#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 inColor;

out vec4 vertexColor;


void main()
{
    vertexColor = vec4(inColor, 1.0f);
    gl_Position = vec4(aPos, 1.0);
}
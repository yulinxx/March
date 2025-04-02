#version 460 core
layout (location = 0) in vec2 aPos;
uniform mat4 projectionMatrix;
void main()
{
    gl_Position = projectionMatrix * vec4(aPos, 1.0);
}

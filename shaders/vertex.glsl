#version 460 core
layout (location = 0) in vec3 iPos;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 color;

uniform float uTime;

void main()
{
    gl_Position = vec4(iPos.xyz, 1.0);
}
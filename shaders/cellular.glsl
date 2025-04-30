#version 460 core
#define M_PI 3.1415926535897932384626433832795
precision highp float;

out vec4 oColor;

uniform vec2  uPos;
uniform float uTime;
uniform vec2  uResolution;

const int COUNT = 53;
vec2 positions[COUNT];

vec2 animPoint(int i)
{
    return sin(positions[i] * 6.28 + uTime / 3.0) * 0.5 + 0.5;
}

vec2 random2(int i)
{
    float s0 = dot(vec2(i), vec2(193.8236));
    float s1 = dot(vec2(i), vec2(363.9113));
    return fract(sin(vec2(s0, s1) * 909.123) * 421.684) * 0.5 + 0.5;
}

void main()
{
    float dist = 1.0;
    vec2 uv = gl_FragCoord.xy / uResolution.xy;

    for (int i = 0; i < COUNT; i++)
    {
        positions[i] = random2(i);
    }

    for (int i = 0; i < positions.length(); i++)
    {
        dist = min(dist, distance(uv, animPoint(i)));
    }

    oColor = vec4(vec3(0.0, dist, 0.0), 1.0);
} 
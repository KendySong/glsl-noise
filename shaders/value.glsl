#version 460 core
#define M_PI 3.1415926535897932384626433832795

out vec4 oColor;

uniform vec2  uPos;
uniform float uTime;
uniform vec2  uResolution;

uniform int   uOctaves;
uniform vec2  uSize;
uniform float uAmplitude;
uniform float uFrequency;
uniform float uLacunarity;
uniform float uPersistence;

float random(vec2 pos)
{
    vec2 s0 = vec2(82437.25346, 34657.95678);
    float r =  fract(sin(dot(pos, s0)) * 981674.73528) * 2.0 - 1.0;
    return r;
}

float noise(vec2 p)
{
    vec2 i = floor(p);
    vec2 f = fract(p);
    vec2 t = smoothstep(0, 1, f);

    float p0 = random(i);
    float p1 = random(i + vec2(1.0, 0.0));
    float p2 = random(i + vec2(0.0, 1.0));
    float p3 = random(i + vec2(1.0, 1.0));

    return mix(mix(p0, p1, t.x), mix(p2, p3, t.x), t.y);
}

void main()
{
    vec2 uv = gl_FragCoord.xy / uResolution.xy;

    float y = 0;
    float amplitude = uAmplitude;
    float frequency = uFrequency;
    for (int i = 0; i < uOctaves; i++)
    {
        y += amplitude * noise((uv + uPos) * uSize * frequency);
        amplitude *= uPersistence;
        frequency *= uLacunarity;
    }

    oColor = vec4(vec3(y * 0.5 + 0.5), 1.0);
} 
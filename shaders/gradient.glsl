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
    return fract(sin(dot(pos, s0)) * 981674.73528) * 2.0 - 1.0;
}

vec2 random2(vec2 pos)
{
    vec2 s0 = vec2(82437.25346, 34657.95678);
    vec2 s1 = vec2(17649.24571, 77453.19436);
    vec2 n  = vec2(dot(pos, s0), dot(pos, s1));
    vec2 f  = fract(sin(n) * 981674.73528) * 2.0 - 1.0;
    
    float angle = atan(f.y / f.x);
    if ((f.y < 0.0 && f.x < 0.0) || (f.y > 0.0 && f.x < 0.0))
        angle += M_PI;
    angle += uTime;
    f = vec2(cos(angle), sin(angle));
      
    return f;
}

vec3 random3(vec3 pos)
{
    vec3 s0 = vec3(82437.25346, 34657.95678, 83656.43612);
    vec3 s1 = vec3(17649.24571, 77453.19436, 64892.98189);
    vec3 s2 = vec3(57571.15983, 22905.65378, 78361.13920);

    vec3 n  = vec3(dot(pos, s0), dot(pos, s1), dot(pos, s2));
    vec3 f  = fract(sin(n) * 981674.73528) * 2.0 - 1.0;  
    return f;
}

float noise2(vec2 p)
{
    vec2 i = floor(p);
    vec2 f = fract(p);
    vec2 t = smoothstep(0.0, 1.0, f);
    
    float p0 = dot(random2(i), f);
    float p1 = dot(random2(i + vec2(1.0, 0.0)), f - vec2(1.0, 0.0));
    float p2 = dot(random2(i + vec2(0.0, 1.0)), f - vec2(0.0, 1.0));
    float p3 = dot(random2(i + vec2(1.0, 1.0)), f - vec2(1.0, 1.0));

    return mix(mix(p0, p1, t.x), mix(p2, p3, t.x), t.y);
}

float noise3(vec3 p)
{
    vec3 i = floor(p);
    vec3 f = fract(p);
    vec3 t = smoothstep(0.0, 1.0, f);

    float p0 = dot(random3(i), f);
    float p1 = dot(random3(i + vec3(1.0, 0.0, 0.0)), f - vec3(1.0, 0.0, 0.0));
    float p2 = dot(random3(i + vec3(0.0, 1.0, 0.0)), f - vec3(0.0, 1.0, 0.0));
    float p3 = dot(random3(i + vec3(1.0, 1.0, 0.0)), f - vec3(1.0, 1.0, 0.0));
    float z0 = mix(mix(p0, p1, t.x), mix(p2, p3, t.x), t.y);

    float p4 = dot(random3(i + vec3(0.0, 0.0, 1.0)), f - vec3(0.0, 0.0, 1.0));
    float p5 = dot(random3(i + vec3(1.0, 0.0, 1.0)), f - vec3(1.0, 0.0, 1.0));
    float p6 = dot(random3(i + vec3(0.0, 1.0, 1.0)), f - vec3(0.0, 1.0, 1.0));
    float p7 = dot(random3(i + vec3(1.0, 1.0, 1.0)), f - vec3(1.0, 1.0, 1.0));
    float z1 = mix(mix(p4, p5, t.x), mix(p6, p7, t.x), t.y);

    return mix(z0, z1, t.z);
}

void main()
{
    vec2 uv = gl_FragCoord.xy / uResolution.xy;

    float y = 0;
    float amplitude = uAmplitude;
    float frequency = uFrequency;
    for (int i = 0; i < uOctaves; i++)
    {
        y += amplitude * noise3(vec3((uv + uPos) * uSize * frequency, uTime));
        amplitude *= uPersistence;
        frequency *= uLacunarity;
    }

    oColor = vec4(vec3(y * 0.5 + 0.5), 1.0);
} 
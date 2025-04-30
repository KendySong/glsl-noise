#version 460 core
#define M_PI 3.1415926535897932384626433832795
precision highp float;

out vec4 oColor;

uniform vec2  uPos;
uniform float uTime;
uniform vec2  uResolution;

vec2 random2(vec2 p)
{
    vec2 s0 = vec2(82437.25346, 34657.95678);
    vec2 s1 = vec2(17649.24571, 77453.19436);
    vec2 n  = vec2(dot(p, s0), dot(p, s1));
    vec2 f  = fract(sin(n) * 981674.73528);
    return f;
}

vec2 animate(vec2 p)
{
    return (sin(6.28 * p + uTime) + 1.0) / 2.0;
}

void main()
{
    vec2 uv = gl_FragCoord.xy / uResolution.xy;
    uv *= vec2(16.0, 9.0);

    vec2 i = floor(uv);
    vec2 f = fract(uv);
    float dist = distance(animate(random2(i)), f);

    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            vec2 nPos = random2(i + vec2(x, y));
            nPos = animate(nPos);
            
            dist = min(dist, distance(nPos + vec2(x, y), f));
        }
    }

    //step(.98, f.x) + step(.98, f.y)
    oColor = vec4(vec3(0.0, pow(dist, 2.5), 0.0), 1.0);
} 
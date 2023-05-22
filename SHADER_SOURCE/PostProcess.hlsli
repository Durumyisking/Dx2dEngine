#include "Sampler.hlsli"
#include "Texture.hlsli"

// postProcess
Texture2D postProcessTexture : register(t60);

cbuffer PostProcess : register(b8)
{
    float2 Resolution;

    float ElapsedTime;
    
    float wave_amount;
    float wave_speed;
    float wave_distortion;

}


struct VSIn
{
    float4 Pos : POSITION;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
};

float2 curve(float2 uv)
{
    uv = (uv - 0.5f) * 2.f;
    uv *= 1.1f;
    uv.x *= 1.f + pow((abs(uv.y) / 5.f), 2.f);
    uv.y *= 1.f + pow((abs(uv.x) / 4.f), 2.f);
    uv = (uv / 2.f) + 0.5f;
    uv = uv * 0.92f + 0.04f;
    return uv;
}

float2 curve2(float2 uv)
{
    uv -= float2(0.5f, 0.5f);
    uv = uv * 1.2f * (1.f / 1.2f + 2.f * uv.x * uv.x * uv.y * uv.y);
    uv += float2(0.5f, 0.5f);
    return uv;
}


float onOff(float a, float b, float c)
{
    return step(c, sin(ElapsedTime + a * cos(ElapsedTime * b)));
}


float noise(float2 uv, Texture2D<float4> noiseTexture)
{
    float2 offset = float2(1.0f, 2.0f * cos(ElapsedTime)) * ElapsedTime * 8.0f + uv * 1.0f; // 노이즈텍스처의 좌표 가져옴 uv와 시간값을 인자로 넘겨주어 노이즈값의 변화를 만듬
    offset = clamp(offset, -1.5f, 2.5f); // 0보다 작은값은 0 1보다큰값은 1로 0~1사이의 값만 나오게 제한한다. (빼도된다)
    float s = noiseTexture.SampleLevel(pointSampler, offset, 0).x; // offset위치에 있는 색의 R값을 가져올것
    s *= s;
    return s;
}


float ramp(float y, float start, float end)
{
    float inside = step(start, y) - step(end, y);
    float fact = (y - start) / (end - start) * inside;
    return (1.f - fact) * inside;
}

float stripesY(float2 uv, Texture2D<float4> noiseTexture)
{
    float noi = noise(uv * float2(0.5f, 1.f) + float2(1.f, 3.f), noiseTexture);
    
    float yValue = uv.y * 4.f + ElapsedTime / 2.f + sin(ElapsedTime + sin(ElapsedTime * 0.63f));
    
    return ramp((yValue, 1.f), 0.3f, 0.4f) * noi;
}

float snow(float2 uv, float scale)
{
    scale *= 5000.f;
    float w = smoothstep(1.f, 0.f, -uv.y * (scale / 10.f));
    if (w < 0.1f)
        return 0.f;
    uv += ElapsedTime / scale;
    uv.y += ElapsedTime * 2.f / scale;
    uv.x += sin(uv.y + ElapsedTime * 0.5f) / scale;
    uv *= scale;
    float2 s = floor(uv);
    float2 f = frac(uv);
    float2 p = float2(0.f, 0.f);
    float k = 3.f, d;
    
    float matR1 = (s + p + scale).x * float2(7.f, 6.f).x + (s + p + scale).y * float2(7.f, 6.f).y;
    float matR2 = (s + p + scale).x * float2(3.f, 5.f).x + (s + p + scale).y * float2(3.f, 5.f).y;
    float2 matR = float2(matR1, matR2);
    
    p = 0.5f + 0.35f * sin(11.f * frac(sin( matR ) * 5.f)) - f;
    d = length(p);
    k = min(d, k);
    k = smoothstep(0.f, k, sin(f.x + f.y) * 0.01f);

    return k * w;
}

float4 MakeGreyScaleColor(float3 _OriginColor)
{    
    return dot(_OriginColor, float3(0.5f, 0.5f, 0.5f));

}

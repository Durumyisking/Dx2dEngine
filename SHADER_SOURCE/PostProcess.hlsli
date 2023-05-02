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
#include "Sampler.hlsli"
#include "Texture.hlsli"

// postProcess
Texture2D postProcessTexture : register(t60);

cbuffer PostProcess : register(b8)
{
    float ElapsedTime;
    float2 Resolution;
    
}
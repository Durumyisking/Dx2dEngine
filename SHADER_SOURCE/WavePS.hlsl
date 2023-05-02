#include "PostProcess.hlsli"

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


float4 main(VSOut _in) : SV_TARGET
{
    float4 color = (float4)0.f;

    //float2 UV = _in.Pos.xy / Resolution;

    //uv.x = uv.x + cos(uv.y * wave_amount + ElapsedTime * wave_speed) / wave_distortion;
    //uv.y = uv.y + sin(uv.x * wave_amount + ElapsedTime * wave_speed) / wave_distortion;
 
    //color = postProcessTexture.Sample(pointSampler, UV);
    
 
    return color;
}
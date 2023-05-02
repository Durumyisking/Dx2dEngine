#include "PostProcess.hlsli"
#include "Blur.hlsli"

float4 main(VSOut _in) : SV_Target
{      
    float4 Color = (float4) 0.f;
        
    // VS_OUT 으로 전달한 SV_Position 값은 PixelShader 에 입력될 때 픽셀좌표로 변환해서 입력
    float2 UV = _in.Pos.xy / Resolution;
        
    float2 fAdd = float2(NoiseTexture.Sample(pointSampler, _in.UV + ElapsedTime * 0.2f).x
                         , NoiseTexture.Sample(pointSampler, _in.UV + float2(0.1f, 0.f) + ElapsedTime * 0.2f).x);
    fAdd -= fAdd / 2.f;
    UV += fAdd * 0.05f;
    
    Color = postProcessTexture.Sample(pointSampler, UV);
    
    return Color;
}
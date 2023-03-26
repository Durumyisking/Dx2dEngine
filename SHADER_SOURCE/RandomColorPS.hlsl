#include "global.hlsli"
Texture2D<float4> noiseTexture : register(t11);
float3 randomColor(float2 uv, float time)
{
    float noiseScale = 2.0;
    float noiseSpeed = 1.0;
    
    float noiseValue = noiseTexture.SampleLevel(pointSampler, uv * noiseScale, 0).r;
    float noiseValue2 = noiseTexture.SampleLevel(pointSampler, uv * noiseScale * 2.0, 0).g;
    float noiseValue3 = noiseTexture.SampleLevel(pointSampler, uv * noiseScale * 4.0, 0).b;
    
    float3 t = float3(cos(time * noiseSpeed), sin(time * noiseSpeed) , 1.f);
    float3 color = float3(noiseValue, noiseValue2, noiseValue3) * t * 0.5 + 0.5;
    
    return color;
}

float4 main(VTX_OUT _in) : SV_Target
{
    float3 color = randomColor(_in.vUV, cbfData2);
    
    return color;
}
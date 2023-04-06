#include "global.hlsli"

float4 main(VTX_OUT _in) : SV_Target
{
    float4 color = RED;
    
    color = defaultTexture.Sample(pointSampler, _in.vUV);
    
    color *= cbxyzw1; // 곱할 색
    color += cbxyzw2; // 더할 색
    
    return color;
}
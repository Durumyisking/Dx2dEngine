#include "global.hlsli"

float4 main(VTX_OUT _in) : SV_Target
{
    float4 color = RED;
    
    color = defaultTexture.Sample(pointSampler, _in.vUV);
    
    return color;
}
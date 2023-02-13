#include "global.hlsli"

float4 PS(VTX_OUT _in) : SV_Target
{
    float4 color = (float) 0.f;
    
    //if (cbxy.x == 1.f)
    //{
    //    return float4(1.f, 1.f, 0.f, 1.f);
    //}
     
    color = defaultTexture.Sample(pointSampler, _in.vUV);
    
    return color;
}
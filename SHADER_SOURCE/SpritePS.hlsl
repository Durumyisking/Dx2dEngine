#include "global.hlsli"

#define INVERSE -1

float4 main(VTX_OUT _in) : SV_Target
{
    
    float4 color = (float) 0.f;
    if (cbiData == INVERSE)
        _in.vUV.x = -_in.vUV.x;
    
    color = defaultTexture.Sample(pointSampler, _in.vUV);       
    
    if (color.a == 0.f)
        discard;
    
    return color;
    
}
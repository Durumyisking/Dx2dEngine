#include "global.hlsli"

float4 main(VTX_OUT _in) : SV_Target
{
    float4 color = (float) 0.f;
   
    if(0 == cbiData)
         _in.vUV.x = -_in.vUV.x;
    
    color = defaultTexture.Sample(pointSampler, _in.vUV);
    
    return color;
}
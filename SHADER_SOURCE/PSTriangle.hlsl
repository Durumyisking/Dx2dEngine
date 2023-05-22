#include "global.hlsli"

float4 main(VTX_OUT _in) : SV_Target
{
    float4 color = (float) 0.f;
    color = defaultTexture.Sample(anisotropicSampler, _in.vUV);
    
    if (color.w == 0.f)
        discard;

    return color;
}
#include "global.hlsli"



float4 main(VTX_OUT _in) : SV_TARGET
{   
    float4 color = { 0.f, 0.f, 0.f, 1.f };
   
    color = defaultTexture.Sample(pointSampler, _in.vUV);
    
//    float alpha = color.w;
    float alpha;
    
    if (cb16_bFadeType == 0) // 0 : fade out, 1 : in
    {
//        alpha -= (cb16_fValue);
        alpha = saturate(1 - (cb16_fValue));
    }
    else if (cb16_bFadeType == 1)
    {
//        alpha += (cb16_fValue);
        alpha = saturate(0 + (cb16_fValue));

    }
//    color.w = alpha;
    
    return color * alpha;
}
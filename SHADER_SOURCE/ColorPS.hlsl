#include "global.hlsli"

float4 main() : SV_TARGET
{  
    float4 color = RGBA;
       
//    float alpha = color.w;
    float alpha;
    
    if (cb16_bFadeType == 0) // 0 : fade out, 1 : in
    {
        alpha = saturate(1 - (cb16_fValue));
    }
    else if (cb16_bFadeType == 1)
    {
        alpha = saturate(0 + (cb16_fValue));

    }    
    
    return RGBA * alpha;
}
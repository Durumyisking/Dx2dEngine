#include "global.hlsli"

float4 main() : SV_TARGET
{  
    float4 color = RGBA;
       
//    float alpha = color.w;
    float alpha;
    
    if (fade_bFadeType == 0) // 0 : fade out, 1 : in
    {
        alpha = saturate(1 - (fade_fValue));
    }
    else if (fade_bFadeType == 1)
    {
        alpha = saturate(0 + (fade_fValue));

    }    
    
    return RGBA * alpha;
}
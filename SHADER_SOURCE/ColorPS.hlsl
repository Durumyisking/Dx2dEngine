#include "global.hlsli"

float4 main() : SV_TARGET
{  
    float4 color = RGBA;
       
//    float alpha = color.w;
    float alpha = 1.f;
    
    if (cbiData2 == 0) // 0 : fade out, 1 : in
    {
        alpha = saturate(1 - (cbfData1));
    }
    else if (cbiData2 == 1)
    {
        alpha = saturate(0 + (cbfData1));
    }    
    
    return RGBA * alpha;
}
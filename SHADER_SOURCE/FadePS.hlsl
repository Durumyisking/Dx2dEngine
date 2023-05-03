#include "global.hlsli"



float4 main(VTX_OUT _in) : SV_TARGET
{   
    float4 color = { 0.f, 0.f, 0.f, 1.f };
   
    // 1이면 텍스처를 fadeinout할거임
    if (cbiData2 == 1)
        color = defaultTexture.Sample(pointSampler, _in.vUV);
    
//    float alpha = color.w;
    float alpha;
    
    if (cbiData1 == 0) // 0 : fade out, 1 : in
    {
        alpha = saturate(1 - (cbfData1));
    }
    else if (cbiData1 == 1)
    {
        alpha = saturate(0 + (cbfData1));

    }
//    color.w = alpha;
    
    return color * alpha;
}
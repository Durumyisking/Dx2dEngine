#include "global.hlsli"

#define INVERSE -1

float4 main(VTX_OUT _in) : SV_Target
{   
    float4 color = (float) 0.f;
    
    if (cbiData == INVERSE)
        _in.vUV.x = 1.f - _in.vUV.x;

    
    if (0 == animationType)
    {
        color = defaultTexture.SampleLevel(pointSampler, _in.vUV, 0.f);
    }
    else if (1 == animationType)
    {
        float diff = (atlasSize - spriteSize) / 2.f;
        float2 UV = (LT - diff - offset) + (atlasSize * _in.vUV);

        if (UV.x < LT.x || UV.y < LT.y || UV.x > LT.x + spriteSize.x || UV.y > LT.y + spriteSize.y)
            discard;
        
        color = atlasTexture.Sample(pointSampler, UV);
    }
    else if (2 == animationType)
    {
        
    }
     
    LightColor lightcolor = (LightColor) 0.f;
    for (int i = 0; i < lightCount; i++)
    {
        CalculateLight(lightcolor, _in.vWorldPos.xyz, i);
    }
    

    color *= lightcolor.diffuse;
    
    
    //float alpha = 1.f;
    
    //if (fade_bFadeType == 0) // 0 : fade out, 1 : in
    //{
    //    alpha = saturate(1 - (fade_fValue));
    //}
    //else if (fade_bFadeType == 1)
    //{
    //    alpha = saturate(0 + (fade_fValue));

    //}
    
    return color;
    
}
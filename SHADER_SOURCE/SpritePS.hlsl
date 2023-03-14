#include "global.hlsli"

#define INVERSE -1

float4 main(VTX_OUT _in) : SV_Target
{   
    float4 color = (float) 0.f;
    
    if (cbiData == INVERSE)
        _in.vUV.x = 1.f - _in.vUV.x;

    
    if (0 == animationType)
    {
        color = defaultTexture.Sample(pointSampler, _in.vUV);
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
 
    
    if (color.a == 0.f)
        discard;
    
    return color;
    
}
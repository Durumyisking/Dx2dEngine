#include "global.hlsli"

#define INVERSE -1

float3 MakeGoldScaleColor(float3 _OriginColor)
{
    return (_OriginColor.rgb += float3(0.75f, 0.55f, 0.15f));
}

float4 main(VTX_OUT _in) : SV_Target
{
    float4 color = (float) 0.f;
    
    if (cbiData1 == INVERSE)
        _in.vUV.x = 1.f - _in.vUV.x;
    
    float diff = (atlasSize - spriteSize) / 2.f; // background¿Í spritesize ³»ÀÇ Gap / 2
    float2 UV = (LT - diff - offset) + (atlasSize * _in.vUV);

    if (UV.x < LT.x || UV.y < LT.y || UV.x > LT.x + spriteSize.x || UV.y > LT.y + spriteSize.y)
        discard;
        
    color = atlasTexture.Sample(pointSampler, UV);
    
    if (color.w == 0)
        discard;
     
    LightColor lightcolor = (LightColor) 0.f;
    for (int i = 0; i < lightCount; i++)
    {
        CalculateLight(lightcolor, _in.vWorldPos.xyz, i);
    }
    
    color *= lightcolor.diffuse;
    
    color.rgb += MakeGoldScaleColor(color.rgb);
    
    float alpharatio = 1.f;
    
    if ((UV.x < laserhit_elapsedX * 10.f) && UV.y < laserhit_elapsedY)
    {
        alpharatio = 0.f;
    }
    if (UV.x < (LT.x - diff) + (laserhit_elapsedX * atlasSize.x))
    {
        alpharatio = 0.f;
    }

    color.a = alpharatio;
     
    if (color.w == 0.f)
        discard;
     
    return color;
}


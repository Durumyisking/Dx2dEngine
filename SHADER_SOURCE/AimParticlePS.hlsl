#include "global.hlsli"

struct GSOutput
{
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
    uint Instance : SV_InstanceID;
};


float4 main(GSOutput In) : SV_TARGET
{
    float4 outColor = (float4) 0.0f;    
 
    outColor = particleBuffer[In.Instance].startColor;
    
    if (outColor.w == 0.f)
        discard;
    
    return outColor;
}
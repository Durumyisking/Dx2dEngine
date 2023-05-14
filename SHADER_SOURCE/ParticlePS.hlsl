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
    float alpharatio = 1.f - particleBuffer[In.Instance].time / particleBuffer[In.Instance].lifeTime;
//    float alpharatio = particleBuffer[In.Instance].time;

    outColor = defaultTexture.Sample(pointSampler, In.UV);    
    outColor = startColor;
    
    outColor.w *= alpharatio;
    
//    outColor = lerp(startColor, endColor, particleBuffer[In.Instance].lifeTime);

    if (outColor.w == 0.f)
        discard;

    
    return outColor;
}
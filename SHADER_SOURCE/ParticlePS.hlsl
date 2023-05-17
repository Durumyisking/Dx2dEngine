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
    
    float fElapsedTime = particleBuffer[In.Instance].elapsedTime;
    float fLifeTime= particleBuffer[In.Instance].lifeTime;

    
    float alpharatio = 1.f - fElapsedTime / fLifeTime;

//    outColor = defaultTexture.Sample(pointSampler, In.UV);    
    outColor = particleBuffer[In.Instance].startColor;

    outColor.a = alpharatio;
    
//    outColor = lerp(startColor, endColor, particleBuffer[In.Instance].lifeTime);

//    outColor.w = alpharatio;
    
    if (outColor.w == 0.f)
        discard;

    
    return outColor;
}
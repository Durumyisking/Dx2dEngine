#include "global.hlsli"

struct VSIn
{
    float4 Pos : POSITION;
    uint iInstance : SV_InstanceID;
};

struct VSOut
{
    float4 Pos : SV_Position;
};

float4 main(VSOut In) : SV_TARGET
{
    float4 outColor = (float4) 0.0f;
    
    outColor = float4(1.0f, 0.0f, 0.0f, 1.0f);
    
    return outColor;

}
#include "global.hlsli"


struct VSOut
{
    float4 Pos : SV_Position;
    uint iInstance : SV_InstanceID;
};

struct GSOutput
{
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
};

StructuredBuffer<Particle> particleBuffer : register(t15);

[maxvertexcount(6)]
void main(point VSOut input[1], inout TriangleStream<GSOutput> output)
{
    GSOutput Out[4] = { (GSOutput) 0.0f, (GSOutput) 0.0f, (GSOutput) 0.0f, (GSOutput) 0.0f };
	
    if (0 == particleBuffer[input[0].iInstance].active)
        return;
	
    float3 vWorldPos = input[0].Pos.xyz + particleBuffer[input[0].iInstance].position.xyz;
    float3 vViewPos = mul(float4(vWorldPos, 1.0f), view);
	
	
    float3 NewPos[4] =
    {
        vViewPos + float3(-0.5f, 0.5f, 0.0f) *  float3(0.01f, 0.01f, 0.01f), // Ω∫ƒ…¿œ
        vViewPos + float3(0.5f, 0.5f, 0.0f) *   float3(0.01f, 0.01f, 0.01f),
        vViewPos + float3(0.5f, -0.5f, 0.0f) *  float3(0.01f, 0.01f, 0.01f),
        vViewPos + float3(-0.5f, -0.5f, 0.0f) * float3(0.01f, 0.01f, 0.01f)
    };
	
    for (int i = 0; i < 4; i++)
    {
        Out[i].Pos = mul(float4(NewPos[i], 1.0f), projection);
    }
	
    Out[0].UV = float2(0.0f, 0.0f);
    Out[1].UV = float2(1.0f, 0.0f);
    Out[2].UV = float2(1.0f, 1.0f);
    Out[3].UV = float2(0.0f, 1.0f);
	
    
    // 0 -- 1
    // | \  |
    // 3 -- 2
    
    output.Append(Out[0]);
    output.Append(Out[1]);
    output.Append(Out[2]);
    output.RestartStrip();
    
    output.Append(Out[0]);
    output.Append(Out[2]);
    output.Append(Out[3]);
    output.RestartStrip();
}
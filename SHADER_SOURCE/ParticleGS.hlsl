#include "global.hlsli"


struct VSOut
{
    float4 Pos : SV_Position;
    uint Instance : SV_InstanceID;
};

struct GSOutput
{
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
    uint Instance : SV_InstanceID;
};


[maxvertexcount(6)]
void main(point VSOut input[1], inout TriangleStream<GSOutput> output) // input은 input output은 output (output 주소에 값을 넣고 그걸 cpu에서 받는 너낌)
{
    GSOutput Out[4] = { (GSOutput) 0.0f, (GSOutput) 0.0f, (GSOutput) 0.0f, (GSOutput) 0.0f };
	
    if (0 == particleBuffer[input[0].Instance].active)
        return;
	
    float3 vWorldPos = particleBuffer[input[0].Instance].position.xyz;
    if (simulationSpace == 0)
    {
        vWorldPos += world._41_42_43;

    }
    float3 vViewPos = mul(float4(vWorldPos, 1.0f), view).xyz;
	
    float3 vScale = particleBuffer[input[0].Instance].startScale;
    //vScale = lerp(20.0f, 50.0f, elapsedTime);
	
	
    float3 NewPos[4] =
    {
        vViewPos + float3(-0.5f, 0.5f, 0.0f) * vScale,
        vViewPos + float3(0.5f, 0.5f, 0.0f) * vScale,
        vViewPos + float3(0.5f, -0.5f, 0.0f) * vScale,
        vViewPos + float3(-0.5f, -0.5f, 0.0f) * vScale
    };
    
    for (int i = 0; i < 4; i++)
    {
        NewPos[i] = RotatePointZ(NewPos[i], particleBuffer[input[0].Instance].radian, vViewPos);
    }
      
	
    for (int j = 0; j < 4; j++)
    {
        Out[j].Pos = mul(float4(NewPos[j], 1.0f), projection);
    }
	
    Out[0].UV = float2(0.0f, 0.0f);
    Out[1].UV = float2(1.0f, 0.0f);
    Out[2].UV = float2(1.0f, 1.0f);
    Out[3].UV = float2(0.0f, 1.0f);
	
    Out[0].Instance = input[0].Instance;
    Out[1].Instance = input[0].Instance;
    Out[2].Instance = input[0].Instance;
    Out[3].Instance = input[0].Instance;
    
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
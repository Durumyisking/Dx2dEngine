#include "global.hlsli"

struct VSIn
{
    float4 Pos : POSITION;
    uint Instance : SV_InstanceID; // drawindexedinstance �ϸ� �ڵ����� ����.
};

struct VSOut
{
    float4 Pos : SV_Position;
    uint Instance : SV_InstanceID;
};

VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
    
    Out.Pos = In.Pos;
    Out.Instance = In.Instance;
    
    return Out;
}


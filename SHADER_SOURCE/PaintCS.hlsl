#include "global.hlsli" 

// SV_GrouptID : �����忡 ���� �׷��� ��ǥ (Z��)
// SV_GroupThreadID : �׷� �� ��������ǥ  (XY��)
// SV_GroupIndex : �׷� �� ������ �ε���  (1����)
// SV_DispatchThreadID : ��ü ������ �������� ȣ��� ��ǥ

float nrand(float2 uv)
{
    return frac(sin(dot(uv, float2(12.9898, 78.233))) * 43758.5453123);
}

uint Hash(uint s)
{
    s ^= 2747636419u;
    s *= 2654435769u;
    s ^= s >> 16;
    s *= 2654435769u;
    s ^= s >> 16;
    s *= 2654435769u;
    return s;
}

float Random(uint seed)
{
    return float(Hash(seed)) / 4294967295.0; // 2^32-1
}


[numthreads(32, 32, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    if(1024 <= DTid.x || 1024 <= DTid.y)
    {
        return;
    }

    float w, h;
    Noisetex.GetDimensions(w, h);
    
 //   float2 uv = float2((float) DTid.x, (float) DTid.y);
    
    Noisetex[DTid.xy] = Random(DTid.x + DTid.y * w);
}
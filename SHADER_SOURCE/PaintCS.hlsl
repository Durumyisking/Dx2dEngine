#include "global.hlsli" 

// SV_GrouptID : 쓰레드에 속한 그룹의 좌표 (Z값)
// SV_GroupThreadID : 그룹 내 쓰레드좌표  (XY값)
// SV_GroupIndex : 그룹 내 쓰레드 인덱스  (1차원)
// SV_DispatchThreadID : 전체 쓰레드 기준으로 호출된 좌표

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
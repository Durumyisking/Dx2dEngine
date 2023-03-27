#include "global.hlsli" 

RWTexture2D<float4> tex : register(u0);

// SV_GrouptID : 쓰레드에 속한 그룹의 좌표 (Z값)
// SV_GroupThreadID : 그룹 내 쓰레드좌표  (XY값)
// SV_GroupIndex : 그룹 내 쓰레드 인덱스  (1차원)
// SV_DispatchThreadID : 전체 쓰레드 기준으로 호출된 좌표


[numthreads(32, 32, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
     
    if(1024 <= DTid.x || 1024 <= DTid.y)
    {
        return;
    }

    tex[DTid.xy] = float4(1.f, 0.f, 0.f, 1.f);

    
}
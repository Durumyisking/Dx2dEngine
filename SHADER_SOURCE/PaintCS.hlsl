#include "global.hlsli" 

RWTexture2D<float4> tex : register(u0);

// SV_GrouptID : �����忡 ���� �׷��� ��ǥ (Z��)
// SV_GroupThreadID : �׷� �� ��������ǥ  (XY��)
// SV_GroupIndex : �׷� �� ������ �ε���  (1����)
// SV_DispatchThreadID : ��ü ������ �������� ȣ��� ��ǥ


[numthreads(32, 32, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
     
    if(1024 <= DTid.x || 1024 <= DTid.y)
    {
        return;
    }

    tex[DTid.xy] = float4(1.f, 0.f, 0.f, 1.f);

    
}
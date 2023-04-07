#include "global.hlsli"

RWStructuredBuffer<Particle> ParticleBuffer : register(u0);
RWStructuredBuffer<ParticleShared> ParticleSharedBuffer : register(u1);


[numthreads(128, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID) // ������ �׷� xyz�� ���ڷ� ����
{
    if (elementCount <= DTid.x) // ������ �ѹ� x���� ������ return (�츰 x�����ϱ�)
        return;
    
    if (ParticleBuffer[DTid.x].active == 0) // ��ƼŬ���� index x�� Ȱ��ȭ�� �ƴϸ�
    {
        while (0 < ParticleSharedBuffer[0].gActiveCount) // �������� ī��Ʈ�� ���� �����´�.
        {
            int originValue = ParticleSharedBuffer[0].gActiveCount; // ex 20����� ����
            int exchange = originValue - 1; // 19�����ȴ�.
            
            // ������ ����ȭ
            // dest���� exchange������ �ٲٴ� ����
            // �ٸ�������� �����.
            //InterlockedExchange(ParticleSharedBuffer[0].gActiveCount, exchange, exchange);
            InterlockedCompareExchange(ParticleSharedBuffer[0].gActiveCount
                                        , originValue, exchange, exchange);
            // ParticleSharedBuffer[0].gActiveCount �ȿ� exchange�� �ִ´�.
            
            if (originValue == exchange) // ���ٴ°� ����ȭ ������? �ٵ� �� ParticleSharedBuffer[0].gActiveCount�� ���ϴ°� �ƴ�����
            {
                ParticleBuffer[DTid.x].active = 1;
                break;
            }
        }
        if (ParticleBuffer[DTid.x].active) // ��ƼŬ ���� active�� 0�ε� ��� ���Ծ�
        {
                // ���������� ��ġ�� ������ �������ش�.
                // ���ø��� �õ��� UV ������ش�.
            float3 Random = (float3) 0.0f;
            float2 UV = float2((float) DTid.x / elementCount, 0.5f); // elementcount�� buffer�� stride
            UV.x += elapsedTime; // ���� uv.x�� ����ð� ���� ������ �������� �ϴ°�
            UV.y += sin((UV.x + elapsedTime) * 3.14592f + 2.0f * 10.0f) * 0.5f; // �굵
                
            Random = float3
                (
                    GaussianBlur(UV + float2(0.0f, 0.0f)).x
                    , GaussianBlur(UV + float2(0.1f, 0.0f)).x
                    , GaussianBlur(UV + float2(0.2f, 0.0f)).x
                ); // ���� ���� uv�� ���� 0.1 0.2������ x��ǥ�� �־���

            ParticleBuffer[DTid.x].position.xyz = Random.xyz * 1000.0f - 1000.0f; // ��ġ ��������
            ParticleBuffer[DTid.x].position.z = 100.0f; // z���� ����
        }
    }
    else // active == 1
    {
        //ParticleBuffer[DTid.x].position += ParticleBuffer[DTid.x].direction 
        //    * ParticleBuffer[DTid.x].speed * deltaTime;
    }
}
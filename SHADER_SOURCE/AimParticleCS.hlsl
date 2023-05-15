#include "global.hlsli"

RWStructuredBuffer<Particle> ParticleBuffer : register(u0);
RWStructuredBuffer<ParticleShared> ParticleSharedBuffer : register(u1);


[numthreads(128, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID) 
{
    if (maxParticles <= DTid.x)
        return;
    
    if (ParticleBuffer[DTid.x].active == 0)
    {
        while (0 < ParticleSharedBuffer[0].gActiveCount) 
        {
            int originValue = ParticleSharedBuffer[0].gActiveCount;
            int exchange = originValue - 1;
            
            // ������ ����ȭ
            // dest���� exchange������ �ٲٴ� ����
            // �ٸ�������� �����.
            //InterlockedExchange(ParticleSharedBuffer[0].gActiveCount, exchange, exchange);
            InterlockedCompareExchange(ParticleSharedBuffer[0].gActiveCount
                                        , originValue, exchange, exchange); // ���� �ٸ��� origin
            // ParticleSharedBuffer[0].gActiveCount �ȿ� exchange�� �ִ´�.
            
            if (originValue == exchange)
            {
                ParticleBuffer[DTid.x].active = 1; // ���� ���⸦ ����
                break;
            } 
        } 
        if (ParticleBuffer[DTid.x].active) // ������ �����ϸ� ����� ����
        {
          
            ParticleBuffer[DTid.x].position.xy = float2(0.f, 0.f); // �ʱ���ġ�� ������ ��ž

            ParticleBuffer[DTid.x].position.z = 1.f; // z���� ����
                       
            if (simulationSpace) // 1 world , 0 local
            {
                ParticleBuffer[DTid.x].position.xyz += worldPosition.xyz;
            }
            
            ////��ƼŬ �ӷ�
            ParticleBuffer[DTid.x].time = 0.f;
            
            ParticleBuffer[DTid.x].lifeTime = maxLifeTime;
        }
    }
    else // active == 1
    {
        ParticleBuffer[DTid.x].time += deltaTime;
        if (ParticleBuffer[DTid.x].lifeTime < ParticleBuffer[DTid.x].time)
        {
            ParticleBuffer[DTid.x].active = 0;
        }
        else
        {
            ParticleBuffer[DTid.x].position 
            += ParticleBuffer[DTid.x].direction * ParticleBuffer[DTid.x].speed * deltaTime;
        }
    }
}

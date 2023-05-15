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
            
            // 스레드 동기화
            // dest값을 exchange값으로 바꾸는 동안
            // 다른스레드는 멈춘다.
            //InterlockedExchange(ParticleSharedBuffer[0].gActiveCount, exchange, exchange);
            InterlockedCompareExchange(ParticleSharedBuffer[0].gActiveCount
                                        , originValue, exchange, exchange); // 값이 다르면 origin
            // ParticleSharedBuffer[0].gActiveCount 안에 exchange를 넣는다.
            
            if (originValue == exchange)
            {
                ParticleBuffer[DTid.x].active = 1; // 위는 여기를 말함
                break;
            } 
        } 
        if (ParticleBuffer[DTid.x].active) // 위에서 성공하면 여기로 들어옴
        {
          
            ParticleBuffer[DTid.x].position.xy = float2(0.f, 0.f); // 초기위치는 레이저 포탑

            ParticleBuffer[DTid.x].position.z = 1.f; // z값은 고정
                       
            if (simulationSpace) // 1 world , 0 local
            {
                ParticleBuffer[DTid.x].position.xyz += worldPosition.xyz;
            }
            
            ////파티클 속력
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

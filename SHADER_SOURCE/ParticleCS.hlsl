#include "global.hlsli"

RWStructuredBuffer<Particle> ParticleBuffer : register(u0);
RWStructuredBuffer<ParticleShared> ParticleSharedBuffer : register(u1);


[numthreads(128, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    if (elementCount <= DTid.x)
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
                                        , originValue, exchange, exchange);
            
            if (originValue == exchange)
            {
                ParticleBuffer[DTid.x].active = 1;
                break;
            }
        }
        if (ParticleBuffer[DTid.x].active)
        {
                // 랜덤값으로 위치와 방향을 설정해준다.
                // 샘플링을 시도할 UV 계산해준다.
            float3 Random = (float3) 0.0f;
            float2 UV = float2((float) DTid.x / elementCount, 0.5f);
            UV.x += elapsedTime;
            UV.y += sin((UV.x + elapsedTime) * 3.14592f + 2.0f * 10.0f) * 0.5f;
                
            Random = float3
                (
                    GaussianBlur(UV + float2(0.0f, 0.0f)).x
                    , GaussianBlur(UV + float2(0.1f, 0.0f)).x
                    , GaussianBlur(UV + float2(0.2f, 0.0f)).x
                );

            ParticleBuffer[DTid.x].position.xyz = Random.xyz * 1000.0f; // - 500.0f;
            ParticleBuffer[DTid.x].position.z = 100.0f;
        }
    }
    else // active == 1
    {
        //ParticleBuffer[DTid.x].position += ParticleBuffer[DTid.x].direction 
        //    * ParticleBuffer[DTid.x].speed * deltaTime;
    }
}
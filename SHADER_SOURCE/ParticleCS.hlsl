//#include "global.hlsli"

//RWStructuredBuffer<Particle> ParticleBuffer : register(u0);
//RWStructuredBuffer<ParticleShared> ParticleSharedBuffer : register(u1);


//[numthreads(128, 1, 1)]
//void main(uint3 DTid : SV_DispatchThreadID) // 쓰레드 그룹 xyz를 인자로 받음
//{
//    if (maxParticles <= DTid.x) // 쓰레드 넘버 x보다 작으면 return (우린 x만쓰니까) 부등호 바뀌어야하나???
//        return;
    
//    if (ParticleBuffer[DTid.x].active == 0) // 파티클버퍼 index x가 활성화가 아니면
//    {
//        while (0 < ParticleSharedBuffer[0].gActiveCount) // 쉐어드버퍼 카운트의 값을 가져온다.
//        {
//            int originValue = ParticleSharedBuffer[0].gActiveCount; // ex 20개라고 하자
//            int exchange = originValue - 1; // 19개가된다.
            
//            // 스레드 동기화
//            // dest값을 exchange값으로 바꾸는 동안
//            // 다른스레드는 멈춘다.
//            //InterlockedExchange(ParticleSharedBuffer[0].gActiveCount, exchange, exchange);
//            InterlockedCompareExchange(ParticleSharedBuffer[0].gActiveCount
//                                        , originValue, exchange, exchange); // 값이 다르면 origin
//            // ParticleSharedBuffer[0].gActiveCount 안에 exchange를 넣는다.
            
//            if (originValue == exchange) // 같다는건 동기화 실패임? 근데 왜 ParticleSharedBuffer[0].gActiveCount랑 비교하는게 아니지요
//            {
//                ParticleBuffer[DTid.x].active = 1; // 위는 여기를 말함
//                break;                                    //^ 
//            }                                             //|
//        }                                                 //|
//        if (ParticleBuffer[DTid.x].active) // 위에서 성공하면 여기로 들어옴
//        {
//            // 랜덤값으로 위치와 방향을 설정해준다.
//            // 샘플링을 시도할 UV 계산해준다.
//            float4 Random = (float4) 0.0f;
//            float2 UV = float2((float) DTid.x / maxParticles, 0.5f); // elementcount는 buffer의 stride 그러니까 stride번째 친구라는뜻
//            UV.x += elapsedTime; // 현재 uv.x에 경과시간 더함 랜덤값 받으려고 하는거
//            UV.y += sin((UV.x + elapsedTime) * 3.14592f + 2.0f * 10.0f) * 0.5f; // 얘도
                
//            Random = float4
//                (
//                    GaussianBlur(UV + float2(0.0f, 0.0f)).x
//                    , GaussianBlur(UV + float2(0.1f, 0.0f)).x
//                    , GaussianBlur(UV + float2(0.2f, 0.0f)).x
//                    , GaussianBlur(UV + float2(0.3f, 0.0f)).x
//                ); // 대충 현재 uv값 부터 0.1 0.2까지의 x좌표를 넣어줌
//              //// radius 원형 범위로 스폰
//            float fTheta = Random.xy * 3.141592f * 2.0f;
//            ParticleBuffer[DTid.x].position.xy = float2(cos(fTheta), sin(fTheta)) * Random.y * radius;
//            ParticleBuffer[DTid.x].position.z = 100.0f; // z값은 고정
            
//            ParticleBuffer[DTid.x].direction.xy 
//                = normalize(float2(ParticleBuffer[DTid.x].position.xy));
            
//            if (simulationSpace) // 1 world , 0 local
//            {
//                ParticleBuffer[DTid.x].position.xyz += worldPosition.xyz;
//            }
            
//            ////파티클 속력
//            ParticleBuffer[DTid.x].time = 0.0f;
//            ParticleBuffer[DTid.x].speed = startSpeed;
//            ParticleBuffer[DTid.x].lifeTime = startLifeTime;
//        }
//    }
//    else // active == 1
//    {
//        ParticleBuffer[DTid.x].time += deltaTime;
//        if (ParticleBuffer[DTid.x].lifeTime < ParticleBuffer[DTid.x].time)
//        {
//            ParticleBuffer[DTid.x].active = 0;
//        }
//        else
//        {
//            ParticleBuffer[DTid.x].position 
//            += ParticleBuffer[DTid.x].direction * ParticleBuffer[DTid.x].speed * deltaTime;
//        }
//    }
//}

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
            InterlockedExchange(ParticleSharedBuffer[0].gActiveCount, exchange, exchange);
            
            if (originValue == exchange)
            {
                ParticleBuffer[DTid.x].active = 1;
                break;
            }
        }
    }
    else // active == 1
    {
        ParticleBuffer[DTid.x].position += ParticleBuffer[DTid.x].direction 
            * ParticleBuffer[DTid.x].speed * deltaTime;
    }
}
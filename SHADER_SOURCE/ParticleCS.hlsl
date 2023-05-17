#include "CSHeader.hlsli"


[numthreads(128, 1, 1)] // 그룹당 쓰레드 개수 ( 우리는 그룹 1개쓰니까 128개만 쓰는거 )
void main(uint3 DTid : SV_DispatchThreadID) // 쓰레드 그룹 xyz를 인자로 받음
{
    if (maxParticles <= DTid.x) // 쓰레드 넘버 x보다 작으면 return (우린 x만쓰니까) 부등호 바뀌어야하나???
        return;
    
    if (ParticleBufferUAV[DTid.x].active == 0) // 파티클버퍼 index x가 활성화가 아니면
    {
        ParticleThreadSync(DTid.x);
        
        if (ParticleBufferUAV[DTid.x].active) // 위에서 성공하면 여기로 들어옴
        {
//            InitalizeParticleBufferUAV(DTid.x, float3(0.f, 0.f, 1.f), float4(0.f, -1.f, 0.f, 1.f), maxLifeTime, 0.f, 0.f);

            // 랜덤값으로 위치와 방향을 설정해준다.
            // 샘플링을 시도할 UV 계산해준다.
            float4 Random = (float4) 0.0f;
            float2 UV = float2((float) DTid.x / maxParticles, 0.5f); // elementcount는 buffer의 stride 그러니까 stride번째 친구라는뜻
         
            Random = GetRandomFromBlur(UV);
          
              //// radius 원형 범위로 스폰
            float2 Theta = Random.xy * 3.141592f * 2.0f;
            ParticleBufferUAV[DTid.x].position.xy = float2(cos(Theta.x), sin(Theta.y)) * Random.y * radius;
//            ParticleBufferUAV[DTid.x].position.x += 200.f;
            ParticleBufferUAV[DTid.x].position.z = 1.0f; // z값은 고정
            
            //ParticleBufferUAV[DTid.x].direction.xy 
            //    = normalize(float2(ParticleBufferUAV[DTid.x].position.xy));
            
            if (simulationSpace) // 1 world , 0 local
            {
                ParticleBufferUAV[DTid.x].position.xyz += worldPosition.xyz;
            }
            
            ////파티클 속력
            ParticleBufferUAV[DTid.x].elapsedTime = 0.f;
            
            float seedx = DTid.x;
            float seedy = DTid.y;
            float r1 = Rand(float2(seedx, seedy));
            float r2 = Rand(float2(seedy, seedx));
            float r3 = Rand(float2(seedx * elapsedTime, seedy));
            float r4 = Rand(float2(seedx, seedy * elapsedTime));
            float r5 = Rand(float2(seedx * elapsedTime, seedy * elapsedTime));
            // [0.5~1] -> [0~1]
            float4 noise =
            {
                2.f * r1 - 1.f,
                2.f * r2 - 1.f,
                2.f * r3 - 1.f,
                2.f * r4 - 1.f
            };
            
//            ParticleBufferUAV[DTid.x].speed = startSpeed;

//          ParticleBufferUAV[DTid.x].lifeTime = 3.f; 
//            ParticleBufferUAV[DTid.x].lifeTime = (maxLifeTime - minLifeTime) * (2.f * r5 - 1.f) + minLifeTime;
          ParticleBufferUAV[DTid.x].lifeTime = maxLifeTime;            
        }
    }
    else // active == 1
    {
        ParticleBufferUAV[DTid.x].elapsedTime += deltaTime;
        if (ParticleBufferUAV[DTid.x].lifeTime < ParticleBufferUAV[DTid.x].elapsedTime)
        {
            ParticleBufferUAV[DTid.x].active = 0;
        }
        else
        {
            ParticleBufferUAV[DTid.x].position 
            += ParticleBufferUAV[DTid.x].direction * ParticleBufferUAV[DTid.x].speed * deltaTime;
        }
    }
}

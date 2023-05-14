#include "global.hlsli"

RWStructuredBuffer<Particle> ParticleBuffer : register(u0);
RWStructuredBuffer<ParticleShared> ParticleSharedBuffer : register(u1);


[numthreads(128, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID) // ������ �׷� xyz�� ���ڷ� ����
{
    if (maxParticles <= DTid.x) // ������ �ѹ� x���� ������ return (�츰 x�����ϱ�) �ε�ȣ �ٲ����ϳ�???
        return;
    
    if (ParticleBuffer[DTid.x].active == 0) // ��ƼŬ���� index x�� Ȱ��ȭ�� �ƴϸ�
    {
        while (0 < ParticleSharedBuffer[0].gActiveCount) // �������� ī��Ʈ�� ���� �����´�.
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
                break; //^ 
            } //|
        } //|
        if (ParticleBuffer[DTid.x].active) // ������ �����ϸ� ����� ����
        {
            // ���������� ��ġ�� ������ �������ش�.
            // ���ø��� �õ��� UV ������ش�.
            float4 Random = (float4) 0.0f;
            float2 UV = float2((float) DTid.x / maxParticles, 0.5f); // elementcount�� buffer�� stride �׷��ϱ� stride��° ģ����¶�
         
            Random = GetRandomFromBlur(UV);
          
              //// radius ���� ������ ����
            float2 Theta = Random.xy * 3.141592f * 2.0f;
            ParticleBuffer[DTid.x].position.xy = float2(cos(Theta.x), sin(Theta.y)) * Random.y * radius;
//            ParticleBuffer[DTid.x].position.x += 200.f;
            ParticleBuffer[DTid.x].position.z = 3.0f; // z���� ����
            
            //ParticleBuffer[DTid.x].direction.xy 
            //    = normalize(float2(ParticleBuffer[DTid.x].position.xy));
            
            if (simulationSpace) // 1 world , 0 local
            {
                ParticleBuffer[DTid.x].position.xyz += worldPosition.xyz;
            }
            
            ////��ƼŬ �ӷ�
            ParticleBuffer[DTid.x].time = 0.f;
            
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
            
            ParticleBuffer[DTid.x].speed = startSpeed;

//          ParticleBuffer[DTid.x].lifeTime = 3.f; 
//            ParticleBuffer[DTid.x].lifeTime = (maxLifeTime - minLifeTime) * (2.f * r5 - 1.f) + minLifeTime;
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

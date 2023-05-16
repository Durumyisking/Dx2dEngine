#include "CSHeader.hlsli"
#include "Random.hlsli"
#include "Blur.hlsli"


[numthreads(128, 1, 1)] // �׷�� ������ ���� ( �츮�� �׷� 1�����ϱ� 128���� ���°� )
void main(uint3 DTid : SV_DispatchThreadID) // ������ �׷� xyz�� ���ڷ� ����
{
    if (maxParticles <= DTid.x) // ������ �ѹ� x���� ������ return (�츰 x�����ϱ�) �ε�ȣ �ٲ����ϳ�???
        return;
    
    if (ParticleBufferUAV[DTid.x].active == 0) // ��ƼŬ���� index x�� Ȱ��ȭ�� �ƴϸ�
    {
        while (0 < ParticleSharedBufferUAV[0].gActiveCount) // �������� ī��Ʈ�� ���� �����´�.
        {
            int originValue = ParticleSharedBufferUAV[0].gActiveCount; 
            int exchange = originValue - 1; 
            
            // ������ ����ȭ
            // dest���� exchange������ �ٲٴ� ����
            // �ٸ�������� �����.
            //InterlockedExchange(ParticleSharedBufferUAV[0].gActiveCount, exchange, exchange);
            InterlockedCompareExchange(ParticleSharedBufferUAV[0].gActiveCount
                                        , originValue, exchange, exchange); // ���� �ٸ��� origin
            // ParticleSharedBufferUAV[0].gActiveCount �ȿ� exchange�� �ִ´�.
            
            if (originValue == exchange) 
            {
                ParticleBufferUAV[DTid.x].active = 1; // ���� ���⸦ ����
                break; //^ 
            } //|
        } //|
        if (ParticleBufferUAV[DTid.x].active) // ������ �����ϸ� ����� ����
        {
            // ���������� ��ġ�� ������ �������ش�.
            // ���ø��� �õ��� UV ������ش�.
            float4 Random = (float4) 0.0f;
            float2 UV = float2((float) DTid.x / maxParticles, 0.5f); // elementcount�� buffer�� stride �׷��ϱ� stride��° ģ����¶�
         
            Random = GetRandomFromBlur(UV);
          
              //// radius ���� ������ ����
            float2 Theta = Random.xy * 3.141592f * 2.0f;
            ParticleBufferUAV[DTid.x].position.xy = float2(cos(Theta.x), sin(Theta.y)) * Random.y * radius;
//            ParticleBufferUAV[DTid.x].position.x += 200.f;
            ParticleBufferUAV[DTid.x].position.z = 1.0f; // z���� ����
            
            //ParticleBufferUAV[DTid.x].direction.xy 
            //    = normalize(float2(ParticleBufferUAV[DTid.x].position.xy));
            
            if (simulationSpace) // 1 world , 0 local
            {
                ParticleBufferUAV[DTid.x].position.xyz += worldPosition.xyz;
            }
            
            ////��ƼŬ �ӷ�
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

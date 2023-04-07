//#include "global.hlsli"

//RWStructuredBuffer<Particle> ParticleBuffer : register(u0);
//RWStructuredBuffer<ParticleShared> ParticleSharedBuffer : register(u1);


//[numthreads(128, 1, 1)]
//void main(uint3 DTid : SV_DispatchThreadID) // ������ �׷� xyz�� ���ڷ� ����
//{
//    if (maxParticles <= DTid.x) // ������ �ѹ� x���� ������ return (�츰 x�����ϱ�) �ε�ȣ �ٲ����ϳ�???
//        return;
    
//    if (ParticleBuffer[DTid.x].active == 0) // ��ƼŬ���� index x�� Ȱ��ȭ�� �ƴϸ�
//    {
//        while (0 < ParticleSharedBuffer[0].gActiveCount) // �������� ī��Ʈ�� ���� �����´�.
//        {
//            int originValue = ParticleSharedBuffer[0].gActiveCount; // ex 20����� ����
//            int exchange = originValue - 1; // 19�����ȴ�.
            
//            // ������ ����ȭ
//            // dest���� exchange������ �ٲٴ� ����
//            // �ٸ�������� �����.
//            //InterlockedExchange(ParticleSharedBuffer[0].gActiveCount, exchange, exchange);
//            InterlockedCompareExchange(ParticleSharedBuffer[0].gActiveCount
//                                        , originValue, exchange, exchange); // ���� �ٸ��� origin
//            // ParticleSharedBuffer[0].gActiveCount �ȿ� exchange�� �ִ´�.
            
//            if (originValue == exchange) // ���ٴ°� ����ȭ ������? �ٵ� �� ParticleSharedBuffer[0].gActiveCount�� ���ϴ°� �ƴ�����
//            {
//                ParticleBuffer[DTid.x].active = 1; // ���� ���⸦ ����
//                break;                                    //^ 
//            }                                             //|
//        }                                                 //|
//        if (ParticleBuffer[DTid.x].active) // ������ �����ϸ� ����� ����
//        {
//            // ���������� ��ġ�� ������ �������ش�.
//            // ���ø��� �õ��� UV ������ش�.
//            float4 Random = (float4) 0.0f;
//            float2 UV = float2((float) DTid.x / maxParticles, 0.5f); // elementcount�� buffer�� stride �׷��ϱ� stride��° ģ����¶�
//            UV.x += elapsedTime; // ���� uv.x�� ����ð� ���� ������ �������� �ϴ°�
//            UV.y += sin((UV.x + elapsedTime) * 3.14592f + 2.0f * 10.0f) * 0.5f; // �굵
                
//            Random = float4
//                (
//                    GaussianBlur(UV + float2(0.0f, 0.0f)).x
//                    , GaussianBlur(UV + float2(0.1f, 0.0f)).x
//                    , GaussianBlur(UV + float2(0.2f, 0.0f)).x
//                    , GaussianBlur(UV + float2(0.3f, 0.0f)).x
//                ); // ���� ���� uv�� ���� 0.1 0.2������ x��ǥ�� �־���
//              //// radius ���� ������ ����
//            float fTheta = Random.xy * 3.141592f * 2.0f;
//            ParticleBuffer[DTid.x].position.xy = float2(cos(fTheta), sin(fTheta)) * Random.y * radius;
//            ParticleBuffer[DTid.x].position.z = 100.0f; // z���� ����
            
//            ParticleBuffer[DTid.x].direction.xy 
//                = normalize(float2(ParticleBuffer[DTid.x].position.xy));
            
//            if (simulationSpace) // 1 world , 0 local
//            {
//                ParticleBuffer[DTid.x].position.xyz += worldPosition.xyz;
//            }
            
//            ////��ƼŬ �ӷ�
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
            
            // ������ ����ȭ
            // dest���� exchange������ �ٲٴ� ����
            // �ٸ�������� �����.
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
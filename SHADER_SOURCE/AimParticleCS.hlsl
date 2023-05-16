#include "CSHeader.hlsli"

[numthreads(128, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID) 
{
    if (maxParticles <= DTid.x)
        return;
    
    if (ParticleBufferUAV[DTid.x].active == 0)
    {
        ParticleThreadSync(DTid.x);

        if (ParticleBufferUAV[DTid.x].active) // 위에서 성공하면 여기로 들어옴
        {            
            InitalizeParticleBufferUAV(DTid.x, float3(0.f, 0.f, 1.f), float4(0.f, -1.f, 0.f, 1.f), maxLifeTime, 0.f, 0.f);
          
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

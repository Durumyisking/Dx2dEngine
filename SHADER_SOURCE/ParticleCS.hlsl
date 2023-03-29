#include "global.hlsli"

RWStructuredBuffer<Particle> ParticleBuffer : register(u0);

[numthreads(128, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    if (elementCount <= DTid.x)
        return;
    
    ParticleBuffer[DTid.x].position += ParticleBuffer[DTid.x].direction 
    * ParticleBuffer[DTid.x].speed * deltaTime;
}
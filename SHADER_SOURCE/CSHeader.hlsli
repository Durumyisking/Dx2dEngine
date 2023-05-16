#include "Particle.hlsli"
#include "Random.hlsli"


void ParticleThreadSync(uint _ThreadID)
{
    while (0 < ParticleSharedBufferUAV[0].gActiveCount)
    {
        int originValue = 0;
        int CurrentSharedBufferActiveCount = ParticleSharedBufferUAV[0].gActiveCount;
        if (CurrentSharedBufferActiveCount <= 0)
        {
            break;
        }
        int expected = CurrentSharedBufferActiveCount;
        int exchange = CurrentSharedBufferActiveCount - 1;
        
            
        InterlockedCompareExchange(ParticleSharedBufferUAV[0].gActiveCount
                                        , expected, exchange, originValue);
            
        if (originValue == expected)
        {
            ParticleBufferUAV[_ThreadID].active = 1;
            break;
        }
    }
}

void InitalizeParticleBufferUAV(uint _ThreadID, float3 _Position, float4 _Direction, float _LifeTime, float _Speed, float _Radian)
{
    ParticleBufferUAV[_ThreadID].position.xy = _Position;
    ParticleBufferUAV[_ThreadID].position.z = 1.f;
    
    if (simulationSpace) // 1 world , 0 local
    {
        ParticleBufferUAV[_ThreadID].position.xyz += worldPosition.xyz;
    }

//    ParticleBufferUAV[_ThreadID].direction = _Direction;
    ParticleBufferUAV[_ThreadID].lifeTime = _LifeTime;
    ParticleBufferUAV[_ThreadID].elapsedTime = 0.f;
//    ParticleBufferUAV[_ThreadID].speed = _Speed;
    ParticleBufferUAV[_ThreadID].radian = _Radian;
}
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

void InitalizeParticleBufferUAV(uint _ThreadID, float3 _Position, float4 _Direction, float3 _Scale, float4 _StartColor, float4 _EndColor, float _LifeTime, float _Speed, float _Radian)
{
    ParticleBufferUAV[_ThreadID].position.xyz = _Position;
    
    if (simulationSpace) // 1 world , 0 local
    {
        ParticleBufferUAV[_ThreadID].position.xyz += worldPosition.xyz;
    }

    _Direction = normalize(_Direction);
    ParticleBufferUAV[_ThreadID].direction = _Direction;
    ParticleBufferUAV[_ThreadID].startScale = _Scale;
    ParticleBufferUAV[_ThreadID].startColor= _StartColor;
    ParticleBufferUAV[_ThreadID].endColor = _EndColor;
//    ParticleBufferUAV[_ThreadID].lifeTime = _LifeTime;
    ParticleBufferUAV[_ThreadID].gravityAcc = 0.f;
    ParticleBufferUAV[_ThreadID].elapsedTime = 0.f;
    ParticleBufferUAV[_ThreadID].speed = _Speed;
    ParticleBufferUAV[_ThreadID].radian = _Radian;
}
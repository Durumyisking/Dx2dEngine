#include "CSHeader.hlsli"

[numthreads(1024, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    if (maxParticles <= DTid.x)
        return;
    
    if (ParticleBufferUAV[DTid.x].active == 0)
    {
        ParticleThreadSync(DTid.x);

        if (ParticleBufferUAV[DTid.x].active)
        {            
            float4 noiseFloat4 = GetRandomFloat4FromNoise(DTid.x, DTid.y);
            
            float RandSpeed = lerp((float) startSpeed, (float) endSpeed, noiseFloat4.x);
            float RandAngle = lerp((float) startAngle, (float) endAngle, noiseFloat4.y);
            float RandRadian = RandAngle * 3.141592f / 180.f;
            
            float2 RightNormal = float2(1.f, 0.f);
            float RotatedX = RightNormal.x * cos(RandRadian) + RightNormal.y * sin(RandRadian);
            float RotatedY = RightNormal.x * sin(RandRadian) - RightNormal.y * cos(RandRadian);
            //float4 Direction = float4(RotatedX, RotatedY, 0.f, 1.f);
            //Direction = normalize(Direction);
            //ParticleBufferUAV[DTid.x].direction = Direction;
            //ParticleBufferUAV[DTid.x].position.z = 1.f;
            float4 Yellow = float4(0.9569f, 0.6672f, 0.4588f, 1.f);
            float4 Orange = float4(0.9569f, 0.6672f, 0.4588f, 1.f);
            InitalizeParticleBufferUAV(DTid.x, float3(0.f, 0.f, 1.f), float4(RotatedX, RotatedY, 0.f, 1.f), float3(0.05f, 0.05f, 1.f), Yellow, Orange, 1.f, RandSpeed, 0.f);
        }
    }
    else  
    {
        ParticleBufferUAV[DTid.x].elapsedTime += deltaTime;
        if (ParticleBufferUAV[DTid.x].lifeTime < ParticleBufferUAV[DTid.x].elapsedTime)
        {
            ParticleBufferUAV[DTid.x].active = 0;
        }
        else
        {
            ParticleBufferUAV[DTid.x].gravityAcc += gravity * deltaTime;
            ParticleBufferUAV[DTid.x].position += ParticleBufferUAV[DTid.x].direction * ParticleBufferUAV[DTid.x].speed * deltaTime;
            ParticleBufferUAV[DTid.x].position.y -= ParticleBufferUAV[DTid.x].gravityAcc.y * deltaTime;
        }
    }
}

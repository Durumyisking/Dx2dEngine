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
            
//            float RandSpeed = lerp((float) startSpeed, (float) endSpeed, noiseFloat4.x);
            float RandAngle = lerp((float) startAngle, (float) endAngle, noiseFloat4.y);
            float RandRadian = RandAngle * (3.141592f / 2.f * -1.f) / 180.f;
            
            float2 RightNormal = float2(1.f, 0.f);
            float RotatedX = RightNormal.x * cos(RandRadian) + RightNormal.y * sin(RandRadian);
            float RotatedY = RightNormal.x * sin(RandRadian) - RightNormal.y * cos(RandRadian);

            int ScaleFlag = GetRandomIntFromNoise(DTid.x, DTid.y, 0, 3);
            float3 RandomSize = (float3)0.f;
            if (ScaleFlag == 0 || ScaleFlag == 1)
            {
                RandomSize = float3(0.01f, 0.01f, 0.f);
            }
            else
            {
                RandomSize = float3(0.01f, 0.1f, 0.f);
            }

            float4 Blue = float4(0.4941f, 0.8118f, 0.9765f, 1.f);
            InitalizeParticleBufferUAV(DTid.x, float3(0.f, 0.f, -0.5f), float4(RotatedX, RotatedY, 0.f, 1.f), RandomSize, Blue, Blue, 1.f, 10.f, 0.f);
//            InitalizeParticleBufferUAV(DTid.x, float3(0.f, 0.f, -0.5f), float4(RotatedX, RotatedY, 0.f, 1.f), RandomSize, Blue, Blue, 1.f, 10.f, RandRadian);
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
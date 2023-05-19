#include "Blur.hlsli"
#include "ConstantBuffer.hlsli"

float Rand(float2 co)
{
    return 0.5 + (frac(sin(dot(co.xy, float2(12.9898, 78.233))) * 43758.5453)) * 0.5;
}


float4 GetRandomFromBlur(float2 _UV)
{
    _UV.x += elapsedTime; // 현재 uv.x에 경과시간 더함 랜덤값 받으려고 하는거
    _UV.y += sin((_UV.x + elapsedTime) * 3.14592f + 2.0f * 10.0f) * 0.5f; // 얘도
    
    float4 Random = float4
                (
                    GaussianBlur(_UV + float2(0.0f, 0.0f)).x
                    , GaussianBlur(_UV + float2(0.1f, 0.0f)).x
                    , GaussianBlur(_UV + float2(0.2f, 0.0f)).x
                    , GaussianBlur(_UV + float2(0.3f, 0.0f)).x
                ); // 대충 현재 uv값 부터 0.1 0.2까지의 x좌표를 넣어줌
    
    return Random;
}


float4 GetRandomFloat4FromNoise(uint _ThreadIDX, uint _ThreadIDY)
{
    float seedx = ((float) _ThreadIDX / (float) maxParticles) + elapsedTime;
    float seedy = ((float) _ThreadIDY / (float) maxParticles) + elapsedTime;
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
    
    return noise;
}

int GetRandomIntFromNoise(uint _ThreadIDX, uint _ThreadIDY, int _Start, int _Range)
{
    float seedx = ((float) _ThreadIDX / (float) maxParticles) + elapsedTime;
    float seedy = ((float) _ThreadIDY / (float) maxParticles) + elapsedTime;
    float r1 = Rand(float2(seedx, seedy));

    // [0.5~1] -> [0.5~Range]
    float noise = (2 * r1 - 1) * _Range;

    // [0~1] -> [Start -> Range]
    int result = (int) noise;
    result += _Start;
    
    return result;
}
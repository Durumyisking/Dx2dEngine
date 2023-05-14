#include "Texture.hlsli"
#include "Light.hlsli"
#include "Particle.hlsli"
#include "Sampler.hlsli"
#include "ConstantBuffer.hlsli"
#include "Blur.hlsli"
#include "Random.hlsli"

struct VTX_IN
{
    float4 vPos : POSITION;                                                     
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;                                
};

struct VTX_OUT
{
    float4 vPos : SV_Position;
    float4 vWorldPos : POSITION;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};



#define ZERO    float4(0.f, 0.f, 0.f, 0.f)

#define RED     float4(1.f, 0.f, 0.f, 1.f)
#define GREEN   float4(0.f, 1.f, 0.f, 1.f)
#define BLUE    float4(0.f, 0.f, 1.f, 1.f)
#define WHITE   float4(1.f, 1.f, 1.f, 1.f)
#define BLACK   float4(0.f, 0.f, 0.f, 1.f)
#define GREY    float4(0.5f, 0.5f, 0.5f, 1.f)
#define YELLOW  float4(1.f, 1.f, 0.f, 1.f)
#define MAGENTA float4(1.f, 0.f, 1.f, 1.f)
#define ALPHA(target, value) float4(target.r, target.g, target.b, (float)value)


float3 RotatePointZ(float3 _point, float _radian)
{
    float cosTheta = cos(_radian);
    float sinTheta = sin(_radian);
    float3 rotatedPoint;
    
    rotatedPoint.x = _point.x * cosTheta - _point.y * sinTheta;
    rotatedPoint.y = _point.x * sinTheta + _point.y * cosTheta;
    rotatedPoint.z = _point.z;
    
    return rotatedPoint;
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
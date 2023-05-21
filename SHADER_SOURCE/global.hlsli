#include "Texture.hlsli"
#include "Light.hlsli"
#include "Particle.hlsli"
#include "Sampler.hlsli"
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


float3 RotatePointZ(float3 _point, float _radian, float3 _rotationCenter)
{
    float cosTheta = cos(_radian);
    float sinTheta = sin(_radian);
    float3 rotatedPoint;
    
    float3 translatedPoint = _point - _rotationCenter;

    rotatedPoint.x = translatedPoint.x * cosTheta - translatedPoint.y * sinTheta;
    rotatedPoint.y = translatedPoint.x * sinTheta + translatedPoint.y * cosTheta;
    rotatedPoint.z = translatedPoint.z;
    
    return rotatedPoint + _rotationCenter;
}
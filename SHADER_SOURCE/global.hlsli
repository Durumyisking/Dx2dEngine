#include "Texture.hlsli"
#include "Light.hlsli"
#include "Particle.hlsli"
#include "Sampler.hlsli"
#include "ConstantBuffer.hlsli"
#include "Blur.hlsli"


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


float Rand(float2 co)
{
    return 0.5 + (frac(sin(dot(co.xy, float2(12.9898, 78.233))) * 43758.5453)) * 0.5;
}


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
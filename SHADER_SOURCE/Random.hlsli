#include "Blur.hlsli"
#include "ConstantBuffer.hlsli"

float Rand(float2 co)
{
    return 0.5 + (frac(sin(dot(co.xy, float2(12.9898, 78.233))) * 43758.5453)) * 0.5;
}


float4 GetRandomFromBlur(float2 _UV)
{
    _UV.x += elapsedTime; // ���� uv.x�� ����ð� ���� ������ �������� �ϴ°�
    _UV.y += sin((_UV.x + elapsedTime) * 3.14592f + 2.0f * 10.0f) * 0.5f; // �굵
    
    float4 Random = float4
                (
                    GaussianBlur(_UV + float2(0.0f, 0.0f)).x
                    , GaussianBlur(_UV + float2(0.1f, 0.0f)).x
                    , GaussianBlur(_UV + float2(0.2f, 0.0f)).x
                    , GaussianBlur(_UV + float2(0.3f, 0.0f)).x
                ); // ���� ���� uv�� ���� 0.1 0.2������ x��ǥ�� �־���
    
    return Random;
}
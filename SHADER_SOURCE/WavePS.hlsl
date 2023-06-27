#include "PostProcess.hlsli"


float4 main(VSOut _in) : SV_Target
{
    float4 Color = (float4) 0.f;

    // ȭ���� ��ǥ�� UV��ǥ�� ��ȯ�Ѵ�.
    float2 UV = _in.Pos.xy / Resolution;

    //// wave speed�� ���� ��������, wave amount�� �ĵ��� ����, distortion�� �������� �� �ܰ�ȴ�.
    //UV.x = UV.x + cos(UV.y * wave_amount + ElapsedTime * wave_speed) / wave_distortion;
    //UV.y = UV.y + sin(UV.x * wave_amount + ElapsedTime * wave_speed) / wave_distortion;
     
    Color = postProcessTexture.Sample(pointSampler, UV);
    
 
    return Color;
}
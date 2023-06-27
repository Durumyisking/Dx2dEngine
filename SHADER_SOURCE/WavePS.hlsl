#include "PostProcess.hlsli"


float4 main(VSOut _in) : SV_Target
{
    float4 Color = (float4) 0.f;

    // 화면의 좌표를 UV좌표로 변환한다.
    float2 UV = _in.Pos.xy / Resolution;

    //// wave speed는 점점 빨라진다, wave amount는 파동의 높이, distortion은 높을수록 덜 외곡된다.
    //UV.x = UV.x + cos(UV.y * wave_amount + ElapsedTime * wave_speed) / wave_distortion;
    //UV.y = UV.y + sin(UV.x * wave_amount + ElapsedTime * wave_speed) / wave_distortion;
     
    Color = postProcessTexture.Sample(pointSampler, UV);
    
 
    return Color;
}
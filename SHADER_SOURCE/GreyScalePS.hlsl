#include "PostProcess.hlsli"
#include "Blur.hlsli"


// https://www.shadertoy.com/view/ldjGzV
float4 main(VSOut _in) : SV_Target
{
    float4 Color = (float4) 0.f;

    float2 UV = _in.Pos.xy / Resolution;

    // UV = curve(UV);
 
    UV = curve2(UV);
    
    Color = postProcessTexture.Sample(pointSampler, UV);
    
    float3 RGB = postProcessTexture.SampleLevel(pointSampler, UV, 0).rgb;
    //float2 look = UV;
    float window = 1.f / (1.f + 20.f * pow((UV.y - fmod(ElapsedTime / 4.f, 1.f)), 2.f));
    //look.x = look.x + sin(look.y * 10.f + ElapsedTime) / 50.f * onOff(4.f, 4.f, 0.3f) * (1.f + cos(ElapsedTime * 80.f)) * window;
    float vShift = 0.4f * onOff(2.f, 3.f, 0.9f) * (sin(ElapsedTime) * sin(ElapsedTime * 20.f) + (0.5f + 0.1f * sin(ElapsedTime * 200.f) * cos(ElapsedTime)));
    //look.y = mod(look.y + vShift, 1.f);
    UV.y = fmod(UV.y + vShift, 1.f);
    RGB += stripesY(UV, NoiseTexture);
    RGB += noise(UV * 2.f, NoiseTexture) / 2.f;
    float vigAmt = 3.f + 0.3f * sin(ElapsedTime + 5.f * cos(ElapsedTime * 5.f));
    float vignette = (1.f - vigAmt * pow((UV.y - 0.5f), 2.f)) * (1.f - vigAmt * pow((UV.x - 0.5f), 2.f));
    RGB *= vignette;
    RGB *= (12.f + fmod(UV.y * 30.f + ElapsedTime, 1.f)) / 13.f;
    
    
    float3 color = RGB;
    float gray = dot(color, float3(0.21f, 0.71f, 0.07f));
    Color = float4(gray, gray, gray, postProcessTexture.Sample(pointSampler, UV).a);

    
//    Color.rgb = RGB;
    
    return Color;
}


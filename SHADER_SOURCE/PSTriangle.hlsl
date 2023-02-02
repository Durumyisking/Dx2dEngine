struct VTX_OUT
{
    float4 vPos : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

Texture2D defaultTexture : register(t0);
SamplerState anisotropicSampler : register(s0);
SamplerState pointSampler : register(s1);



float4 PS(VTX_OUT _in) : SV_Target
{
    float4 color = (float) 0.f;
     
    color = defaultTexture.Sample(anisotropicSampler, _in.vUV);
    
    return color;
}
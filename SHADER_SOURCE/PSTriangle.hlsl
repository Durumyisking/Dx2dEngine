struct VTX_OUT
{
    float4 vPos : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

Texture2D defaultTexture : register(t0);

SamplerState pointSampler : register(s0);
SamplerState linearSampler : register(s1);
SamplerState anisotropicSampler : register(s2);


cbuffer Material : register(b1)
{
    int cbiData;
    float cbfData;
    float2 cbxy;
    float3 cbxyz;
    float4 cbxyzw;
    matrix cbmat;
}


float4 PS(VTX_OUT _in) : SV_Target
{
    float4 color = (float) 0.f;
    
    //if (cbxy.x == 1.f)
    //{
    //    return float4(1.f, 1.f, 0.f, 1.f);
    //}
     
    color = defaultTexture.Sample(pointSampler, _in.vUV);
    
    return color;
}
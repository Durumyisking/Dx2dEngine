struct VTX_IN
{
    float4 vPos : POSITION; // 오른쪽에 오는놈은 시멘틱이라고 해요
                            // 태그같은거임
                            // 외부에서 태그 적으면 해당 바이트 크기(12) 만큼 보내겠다~
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD; // 텍스처 UV좌표 (픽셀쉐이더에서 할 수 있지민 U*V만큼 연산해줘야되니까 버텍스 쉐이더에서 넘겨줘서 보간하게끔 한다)
                            
    
};

struct VTX_OUT
{
    float4 vPos : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

cbuffer Transform : register(b0) // 그래픽카드 레지스터(상수버퍼)의  b0을 상수버퍼로 쓸거임
{
    float4 cbPos;
}

cbuffer Material : register(b1)
{
    int iData;
    float fData;
    float2 xy;
    float3 xyz;
    float4 xyzw;
    matrix mat;
}


SamplerState pointSampler : register(s0);
SamplerState linearSampler : register(s1);
SamplerState anisotropicSampler : register(s2);

VTX_OUT VS(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.0f; // 초기화
//    vColor = defaultTexture.Sample(samplerState, _in.vUV);
    
    output.vPos = float4(_in.vPos + cbPos); // float 3까지는 vpos쓰고 w로는 1.f 쓸거임
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;

    return output; // 얘를 레스터라이저에 보내줌
}
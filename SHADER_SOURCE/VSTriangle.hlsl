struct VTX_IN
{
    float4 vPos : POSITION; // �����ʿ� ���³��� �ø�ƽ�̶�� �ؿ�
                            // �±װ�������
                            // �ܺο��� �±� ������ �ش� ����Ʈ ũ��(12) ��ŭ �����ڴ�~
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD; // �ؽ�ó UV��ǥ (�ȼ����̴����� �� �� ������ U*V��ŭ ��������ߵǴϱ� ���ؽ� ���̴����� �Ѱ��༭ �����ϰԲ� �Ѵ�)
                            
    
};

struct VTX_OUT
{
    float4 vPos : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

cbuffer Transform : register(b0) // �׷���ī�� ��������(�������)��  b0�� ������۷� ������
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
    VTX_OUT output = (VTX_OUT) 0.0f; // �ʱ�ȭ
//    vColor = defaultTexture.Sample(samplerState, _in.vUV);
    
    output.vPos = float4(_in.vPos + cbPos); // float 3������ vpos���� w�δ� 1.f ������
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;

    return output; // �긦 �����Ͷ������� ������
}
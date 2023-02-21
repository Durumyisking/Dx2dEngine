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


cbuffer Transform : register(b0)
{
    row_major matrix world;
    row_major matrix view;
    row_major matrix projection;
}

cbuffer Material : register(b1)
{
    int cbiData;
    float cbfData;
    float2 cbxy;
    float3 cbxyz;
    float4 cbxyzw;
    matrix cbmat;
}

cbuffer Grid : register(b2)
{
    float4 cameraPosition;
    float2 cameraScale;
    float2 resolution;
}

Texture2D defaultTexture : register(t0);

SamplerState pointSampler : register(s0);
SamplerState linearSampler : register(s1);
SamplerState anisotropicSampler : register(s2);

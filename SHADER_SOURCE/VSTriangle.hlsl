
struct VTX_IN
{
    float3 vPos : POSITION; // �����ʿ� ���³��� �ø�ƽ�̶�� �ؿ�
                            // �±װ�������
                            // �ܺο��� �±� ������ �ش� ����Ʈ ũ��(12) ��ŭ �����ڴ�~
    float4 vColor : COLOR;
    
};

struct VTX_OUT
{
    float4 vPos : SV_Position;
    float4 vColor : COLOR;
};

cbuffer Transform : register(b0) // �׷���ī�� ��������(�������)��  b0�� ������۷� ������
{
    float4 cbPos;
}

VTX_OUT VS(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.0f; // �ʱ�ȭ
    output.vPos = float4(_in.vPos + cbPos.xyz, 1.f); // float 3������ vpos���� w�δ� 1.f ������
    output.vColor = _in.vColor;

    return output; // �긦 �����Ͷ������� ������
}
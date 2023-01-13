
struct VTX_IN
{
    float3 vPos : POSITION; // �����ʿ� ���³��� �ø�ƽ�̶�� �ؿ�
                            // �±װ�������
    float4 vColor : COLOR;
    
};

struct VTX_OUT
{
    float4 vPos : SV_Position;
    float4 vColor : COLOR;
};

float4 main(VTX_IN _in) : SV_POSITION
{
    VTX_OUT output = (VTX_OUT) 0.0f; // �ʱ�ȭ
    output.vPos = float4(_in.vPos, 1.f); // float 3������ vpos���� w�δ� 1.f ������
    output.vColor = _in.vColor;

	return output; // �긦 �����Ͷ������� ������
}
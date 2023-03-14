#include "global.hlsli"


float4 PSMain(VTX_OUT _in) : SV_Target
{
    // ����ũ �ؽ�ó���� �ش� �ȼ� ��ġ�� ���� ���� �����ɴϴ�.
    float4 maskColor = PixelCollisionTexture.Sample(pointSampler, _in.vUV);
    float4 color = maskColor;

    // ����ũ �ؽ�ó���� ������ ���� ���� ���(1.0)�� ��� �浹�� ó���մϴ�.
    if (maskColor.r == 1.f && maskColor.g == 0.f && maskColor.b == 1.f)
    {
        // �浹 ó�� ������ �ۼ��մϴ�.
        // ���� ���, �ش� �ȼ��� ���� ���� �����ϰų� Ư���� ȿ���� �߰��� �� �ֽ��ϴ�.
        color = float4(1.0, 0.0, 0.0, 1.0); // ���������� ����
    }

    return color;
}





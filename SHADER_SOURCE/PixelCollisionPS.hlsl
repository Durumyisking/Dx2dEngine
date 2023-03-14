#include "global.hlsli"


float4 PSMain(VTX_OUT _in) : SV_Target
{
    // 마스크 텍스처에서 해당 픽셀 위치의 색상 값을 가져옵니다.
    float4 maskColor = PixelCollisionTexture.Sample(pointSampler, _in.vUV);
    float4 color = maskColor;

    // 마스크 텍스처에서 가져온 색상 값이 흰색(1.0)인 경우 충돌로 처리합니다.
    if (maskColor.r == 1.f && maskColor.g == 0.f && maskColor.b == 1.f)
    {
        // 충돌 처리 로직을 작성합니다.
        // 예를 들어, 해당 픽셀의 색상 값을 변경하거나 특별한 효과를 추가할 수 있습니다.
        color = float4(1.0, 0.0, 0.0, 1.0); // 빨간색으로 변경
    }

    return color;
}





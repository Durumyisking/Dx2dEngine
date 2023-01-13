
struct VTX_IN
{
    float3 vPos : POSITION; // 오른쪽에 오는놈은 시멘틱이라고 해요
                            // 태그같은거임
    float4 vColor : COLOR;
    
};

struct VTX_OUT
{
    float4 vPos : SV_Position;
    float4 vColor : COLOR;
};

float4 main(VTX_IN _in) : SV_POSITION
{
    VTX_OUT output = (VTX_OUT) 0.0f; // 초기화
    output.vPos = float4(_in.vPos, 1.f); // float 3까지는 vpos쓰고 w로는 1.f 쓸거임
    output.vColor = _in.vColor;

	return output; // 얘를 레스터라이저에 보내줌
}
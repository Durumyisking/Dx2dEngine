#include "Light.hlsli"
#include "Particle.hlsli"
#include "ConstantBuffer.hlsli"
#include "Texture.hlsli"
#include "Sampler.hlsli"



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
    float4 vWorldPos : POSITION;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};



#define ZERO    float4(0.f, 0.f, 0.f, 0.f)

#define RED     float4(1.f, 0.f, 0.f, 1.f)
#define GREEN   float4(0.f, 1.f, 0.f, 1.f)
#define BLUE    float4(0.f, 0.f, 1.f, 1.f)
#define WHITE   float4(1.f, 1.f, 1.f, 1.f)
#define BLACK   float4(0.f, 0.f, 0.f, 1.f)
#define GREY    float4(0.5f, 0.5f, 0.5f, 1.f)
#define YELLOW  float4(1.f, 1.f, 0.f, 1.f)
#define MAGENTA float4(1.f, 0.f, 1.f, 1.f)
#define ALPHA(target, value) float4(target.r, target.g, target.b, (float)value)



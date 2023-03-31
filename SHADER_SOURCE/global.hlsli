#include "Light.hlsli"
#include "Particle.hlsli"

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


cbuffer Transform : register(b0)
{
    row_major matrix world;
    row_major matrix view;
    row_major matrix projection;
}

cbuffer Material : register(b1)
{
    int cbiData1;
    int cbiData2;
    int cbiData3;
    int cbiData4;
    
    float cbfData1;
    float cbfData2;
    float cbfData3;
    float cbfData4;
    
    float2 cbxy1;
    float2 cbxy2;
    float2 cbxy3;
    float2 cbxy4;
    
    float3 cbxyz1;
    float cbxyzPadding1;
    float3 cbxyz2;
    float cbxyzPadding2;
    float3 cbxyz3;
    float cbxyzPadding3;
    float3 cbxyz4;
    float cbxyzPadding4;
    
    float4 cbxyzw1;
    float4 cbxyzw2;
    float4 cbxyzw3;
    float4 cbxyzw4;
    
    matrix cbmat1;
    matrix cbmat2;
    matrix cbmat3;
    matrix cbmat4;
}

cbuffer Grid : register(b2)
{
    float4 cameraPosition;
    float2 cameraScale;
    float2 resolution;
}

cbuffer Color : register(b3)
{
    float4 RGBA;
}

cbuffer Animation : register(b4)
{
    float2 LT;
    float2 spriteSize;
    float2 offset;
    float2 atlasSize;

    uint animationType;
}


cbuffer LightCount : register(b5)
{
    uint lightCount;
}
cbuffer ParticleSystem : register(b6)
{
    float4 particleColor;
    uint elementCount;
    float deltaTime;
}



Texture2D defaultTexture : register(t0);
Texture2D atlasTexture : register(t12);


StructuredBuffer<LightAttribute> lightAttributes : register(t13);
StructuredBuffer<Particle> particleBuffer : register(t15);

SamplerState pointSampler : register(s0);
SamplerState linearSampler : register(s1);
SamplerState anisotropicSampler : register(s2);


#define RED     float4(1.f, 0.f, 0.f, 1.f)
#define GREEN   float4(0.f, 1.f, 0.f, 1.f)
#define BLUE    float4(0.f, 0.f, 1.f, 1.f)
#define WHITE   float4(1.f, 1.f, 1.f, 1.f)
#define BLACK   float4(0.f, 0.f, 0.f, 1.f)
#define GREY    float4(0.5f, 0.5f, 0.5f, 1.f)
#define YELLOW  float4(1.f, 1.f, 0.f, 1.f)
#define MAGENTA float4(1.f, 0.f, 1.f, 1.f)
#define ALPHA(target, value) float4(target.r, target.g, target.b, (float)value)


void CalculateLight(in out LightColor _lightColor, float3 _position, int _idx) // in out 키워드는 참조/포인터로 쓸거임
{
    if(0 == lightAttributes[_idx].type)
    {
        _lightColor.diffuse += lightAttributes[_idx].color.diffuse;
        
    }
    else if (1 == lightAttributes[_idx].type)
    {
        float dist= distance(lightAttributes[_idx].position.xy, _position.xy); // z값을 연산해주자.
        
        if(dist < lightAttributes[_idx].radius)
        {
            float ratio = 1.f - (dist / lightAttributes[_idx].radius);
            _lightColor.diffuse += lightAttributes[_idx].color.diffuse * ratio;
        }

    }
       
}
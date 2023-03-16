#include "Light.hlsli"

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
    float3 vWorldPos : POSITION;
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

cbuffer Fade : register(b3)
{
    float cb16_fValue;
    int   cb16_bFadeType;
    int   cb16_bTextureType;
}

cbuffer Color : register(b4)
{
    float4 RGBA;
}

cbuffer Animation : register(b5)
{
    float2 LT;
    float2 spriteSize;
    float2 offset;
    float2 atlasSize;

    uint animationType;
}


cbuffer LightCount : register(b6)
{
    uint lightCount;
}



Texture2D defaultTexture : register(t0);
// atlas TextureType
Texture2D atlasTexture : register(t12);


SamplerState pointSampler : register(s0);
SamplerState linearSampler : register(s1);
SamplerState anisotropicSampler : register(s2);


StructuredBuffer<LightAttribute> lightAttributes : register(t13);

void CalculateLight(in out LightColor _lightColor, float3 _position, int _idx) // in out 키워드는 참조/포인터로 쓸거임
{
    if(0 == lightAttributes[_idx].type)
    {
        _lightColor.diffuse += lightAttributes[_idx].color.diffuse;
        
    }
    else if (1 == lightAttributes[_idx].type)
    {
        float dist= distance(lightAttributes[_idx].position.xy, _position.xy);
        
        if(dist < lightAttributes[_idx].radius)
        {
            float ratio = 1.f - (dist / lightAttributes[_idx].radius);
            _lightColor.diffuse += lightAttributes[_idx].color.diffuse * ratio;
        }

    }
       
}
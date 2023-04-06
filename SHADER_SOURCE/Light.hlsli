
struct LightColor
{
    float4 diffuse;
    float4 specular;
    float4 ambient;
    
};

struct LightAttribute
{
    LightColor color;
    float4 position;
    float4 direction;
    
    float radius;
    float angle;    

    int type;
    
    int padding;

};


StructuredBuffer<LightAttribute> lightAttributes : register(t13);
StructuredBuffer<LightAttribute> lightAttributes3D : register(t14);


void CalculateLight(in out LightColor _lightColor, float3 _position, int _idx) // in out 키워드는 참조/포인터로 쓸거임
{
    if (0 == lightAttributes[_idx].type)
    {
        _lightColor.diffuse += lightAttributes[_idx].color.diffuse;
        
    }
    else if (1 == lightAttributes[_idx].type)
    {
        float dist = distance(lightAttributes[_idx].position.xy, _position.xy); // z값을 연산해주자.
        
        if (dist < lightAttributes[_idx].radius)
        {
            float ratio = 1.f - (dist / lightAttributes[_idx].radius);
            _lightColor.diffuse += lightAttributes[_idx].color.diffuse * ratio;
        }

    }
       
}
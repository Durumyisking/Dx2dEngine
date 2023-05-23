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
    float cbfData5;
    float cbfData6;
    float cbfData7;
    float cbfData8;
    
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
    float4 worldPosition;
    float4 startSize;
    float4 startColor;
    float4 endColor;
    
    uint maxParticles;
    uint simulationSpace;
    float radius;
    float deltaTime;
    
    float startSpeed;
    float endSpeed;
    float maxLifeTime;
    float minLifeTime;
    
    float startAngle;
    float endAngle;
    float elapsedTime;
    float gravity;    

    float force;
    float radian;
    int2 padding;    
}

cbuffer LaserHit : register(b9)
{
    float laserhit_ElapsedX;
    float laserhit_ElapsedY;
    float laserhit_PrevElapsedY;
}

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
    float4 worldPosition; // 컬러 맥스파티클 델타타임
    float4 startColor;
    float4 endColor;
    float4 startSize;
    
    uint maxParticles;
    uint simulationSpace;
    float radius;
    float startSpeed;
    
    float maxLifeTime;
    float minLifeTime;
    float deltaTime;
    float elapsedTime; //누적시간

    float gravity;    
    float force;
    int padding1;
    int padding2;

}

//cbuffer Noise : register(b7)
//{
//    float4 NoiseSize;
//}


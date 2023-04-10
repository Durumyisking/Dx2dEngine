
struct Particle
{
    float4 position;
    float4 direction;
    
    float lifeTime;
    float time;
    float speed;
    float radian;
    uint active;
};


struct ParticleShared
{
    uint gActiveCount;
};

StructuredBuffer<Particle> particleBuffer : register(t15);


struct Particle
{
    float4 position;
    float4 direction;
    
    float lifeTime;
    float elapsedTime;
    float speed;
    float radian;
    uint active;
};


struct ParticleShared
{
    uint gActiveCount;
};

StructuredBuffer<Particle> particleBuffer : register(t15);
RWStructuredBuffer<Particle> ParticleBufferUAV : register(u0);
RWStructuredBuffer<ParticleShared> ParticleSharedBufferUAV : register(u1);

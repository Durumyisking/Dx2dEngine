#include "PostProcess.hlsli"

#define cc float2(0.5f ,0.5f )
#define smoothness 1.f
#define SNOW_COL float4(1.f, 1.f,1.f,1.f)
#define N_LAYERS 8.f
#define SNOW_ALPHA 5.f
#define SPEED 0.3f
#define bg float4(0.8f,0.8f,0.9f,1.f)




float smoothCircle(float2 position, float relativeSize)
{
    float d = distance(cc, position) * 2.0f / relativeSize;
    if (d > 1.0f)
    {
        return 0.0f;
    }
    else
    {
        return clamp(smoothness / d - smoothness, -1.0f, 1.0f);
    }
}

float randF(float n)
{
    return frac(sin(n) * 43758.5453123f);
}

// used to determine whether to draw a flake in the grid
// the magic number is just me mashing the keyboard
bool rand2d(float i, float j, float probability)
{
    return (randF(i + j * 7.8124861f) > probability);
}


// create the grid of circles, with a bunch missing, and fanaggle the sizes a bit
float circleGrid(float2 position, float spacing, float dotSize)
{
    
    // idx => which dot we are showing in the grid.
    
    // check x and y index to see if we should draw it or not.
    float idx = floor(1.0f / spacing * position.x);
    float yIdx = floor(1.0f / spacing * position.y);

    // much higher than .06 causes the grid to be obvious
    if (rand2d(idx, yIdx, 0.06f))
    {
        return 0.0f;
    }
    
    // modify the size of the flake a bit
    float relativeSize = (0.5f + 0.5f * randF(yIdx)) * dotSize / spacing;
    
    return smoothCircle(float2(
        frac(1.0f / spacing * position.x),
        frac(1.0f / spacing * position.y + yIdx)
    ), relativeSize);
}


float4 main(VSOut _in) : SV_Target
{      
    float4 Color = postProcessTexture.Sample(pointSampler, _in.UV); // 기존 코드
    
    float2 uvsq = float2(_in.UV.x * Resolution.x / Resolution.y, _in.UV.y);
    float amnt = 0.f;
    
    for (float i = 0.0; i < N_LAYERS; i++)
    {
        float p = 0.5f + ((i + 1.f) / N_LAYERS) * 0.4f;
        float2 fallPosition = float2(
            uvsq.x + i + p * sin(ElapsedTime / 2.f + i) / 4.f * SPEED,
            i * 3.f + uvsq.y - ElapsedTime * p / 1.f * SPEED
        );
        amnt = amnt + SNOW_ALPHA * circleGrid(fallPosition, 0.06f * p, 0.04f * p * p);
    }
    
    float4 snowColor = lerp(SNOW_COL, bg, 1.0 - amnt);
    Color.rgb = snowColor.rgb * Color.rgb; // 뷰포트 색상과 눈을 더합니다.
    
    return Color;
}



#include "global.hlsli" 


RWTexture2D<float4> Noisetex : register(u0);

// SV_GrouptID : 쓰레드에 속한 그룹의 좌표 (Z값)
// SV_GroupThreadID : 그룹 내 쓰레드좌표  (XY값)
// SV_GroupIndex : 그룹 내 쓰레드 인덱스  (1차원)
// SV_DispatchThreadID : 전체 쓰레드 기준으로 호출된 좌표

float nrand(float2 uv, float3 xyz)
{
    return frac(sin(dot(uv, float2(xyz.x, xyz.y))) * xyz.z);
}



[numthreads(32, 32, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
     
    if(1024 <= DTid.x || 1024 <= DTid.y)
    {
        return;
    }

    float w, h;
    Noisetex.GetDimensions(w, h);
//    uint test = DTid.x % 10;
    float2 uv = float2(DTid.x, DTid.y);
    
    //Noisetex[DTid.xy] = nrand(uv);
    
        float r;
        float g;
        float b;

    
        if (0 <= DTid.x && 320 > DTid.x)
        {
            if (0 <= DTid.y && 64 > DTid.y)
            {
                uv = float2(32, 32);
            }
            else if (64 <= DTid.y && 128 > DTid.y)
            {
                uv = float2(96, 96);
            }
            else if (128 <= DTid.y && 192 > DTid.y)
            {
                uv = float2(160, 160);
            }
            else if (192 <= DTid.y && 256 > DTid.y)
            {
                uv = float2(224, 224);
            }
            else if (256 <= DTid.y && 320 > DTid.y)
            {
                uv = float2(288, 288);
            }

        }
        else if (341 <= DTid.x && 642 > DTid.x)
        {
        uv = float2(500, 500);
        }
        else if (642 <= DTid.x && 1024 > DTid.x)
        {
        uv = float2(700, 700);
        }
    
        r = lerp(cbfData2, cbfData3, nrand(uv, cbxyz));
        g = lerp(cbfData3, cbfData4, nrand(uv, cbxyz));
        b = lerp(cbfData4, cbfData2, nrand(uv, cbxyz));
        Noisetex[DTid.xy] = float4(r, g, b, 1.f);

    

 //   float2 uv = float2((float) DTid.x, (float) DTid.y);
    
}
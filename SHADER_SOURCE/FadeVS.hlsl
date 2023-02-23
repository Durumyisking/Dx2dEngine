#include "global.hlsli"


VTX_OUT main(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f; // √ ±‚»≠
    
    float4 worldPosition = mul(_in.vPos, world);
    float4 viewPosition = mul(worldPosition, view);
    float4 projectionPosition = mul(viewPosition, projection);
    
    output.vPos = projectionPosition;
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;

       
    return output;
}
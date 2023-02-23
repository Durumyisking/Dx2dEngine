#include "global.hlsli"


VTX_OUT main(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f; // √ ±‚»≠
    
    float4 worldPosition = mul(_in.vPos, Fadeworld);
    float4 viewPosition = mul(worldPosition, Fadeview);
    float4 projectionPosition = mul(viewPosition, Fadeprojection);
    
    output.vPos = projectionPosition;
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;

       
    return output;
}
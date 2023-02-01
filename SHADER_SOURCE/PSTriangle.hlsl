struct VTX_OUT
{
    float4 vPos : SV_Position;
    float4 vColor : COLOR;
};

//texture tex()


float4 PS(VTX_OUT _in) : SV_Target
{
    return _in.vColor;
}
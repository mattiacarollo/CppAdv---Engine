//--------------------------------------------------------------------------------------
// Copyright (c) Luca Giona 2013. Do not distribute. (Master Game Development - University of Verona)
//--------------------------------------------------------------------------------------

struct PixelShaderInput
{
    float4 pos : SV_POSITION;
	float4 col : COLOR0;
};

float4 SimplePixelShader(PixelShaderInput input) : SV_TARGET
{
    return input.col;
}

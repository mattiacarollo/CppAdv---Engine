//--------------------------------------------------------------------------------------
// Copyright (c) Luca Giona 2013. Do not distribute. (Master Game Development - University of Verona)
//--------------------------------------------------------------------------------------

cbuffer TransformsBuffer
{
	float4x4 World;
	float4x4 View;
	float4x4 Projection;
	float3 CameraPosition;
};

struct VertexShaderInput
{
	float3 pos : POSITION;
	float4 col : COLOR;
};

struct PixelShaderInput
{
    float4 pos : SV_POSITION;
	float4 col : COLOR0;
};

PixelShaderInput SimpleVertexShader(VertexShaderInput input)
{
    PixelShaderInput output;

	output.pos = mul( World, float4(input.pos, 1.0f) );
    output.pos = mul( View, output.pos );
    output.pos = mul( Projection, output.pos );

	output.col = input.col;

    return output;
}

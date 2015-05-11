/////////////
// GLOBALS //
/////////////
//In shader programs you begin with the global variables. These globals can be modified externally from your C++ code
//Generally you will put most globals in buffer object types called "cbuffer" even if it is just a single global variable.
//Logically organizing these buffers is important for efficient execution of shaders as well as how the graphics card will store the buffers.
//In this example I've put three matrices in the same buffer since I will update them each frame at the same time.
cbuffer MatrixBuffer
{
	matrix worldMatrix; //  potrebbe essere matrix <float,4,4>
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer CameraBuffer
{
	float3 cameraPosition;
	float padding;
};

//////////////
// TYPEDEFS //
//////////////
//We are creating types that have x, y, z, w position vectors and red, green, blue, alpha colors.
//Semantics are different for vertex and pixel shaders
//POSITION works for vertex shaders and SV_POSITION works for pixel shaders while COLOR works for both
struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0; // Le nostre coordinate texture, UV position
	float3 normal : NORMAL; //sono le normali, un vector3
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 viewDirection : TEXCOORD1;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
//The vertex shader is called by the GPU when it is processing data from the vertex buffers that have been sent to it. 
//This vertex shader which I named ColorVertexShader will be called for every single vertex in the vertex buffer.
PixelInputType LightVertexShader(VertexInputType input)
{
	PixelInputType output;
	float4 worldPosition;

	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Store the input color for the pixel shader to use.
	output.tex = input.tex;

	// Calculate the normal vector against the world matrix only.
	output.normal = mul(input.normal, (float3x3)worldMatrix);

	// Normalize the normal vector.
	output.normal = normalize(output.normal);

	// Calculate the position of the vertex in the world.
	worldPosition = mul(input.position, worldMatrix);

	// Determine the viewing direction based on the position of the camera and the position of the vertex in the world.
	output.viewDirection = cameraPosition.xyz - worldPosition.xyz;

	// Normalize the viewing direction vector.
	output.viewDirection = normalize(output.viewDirection);

	return output;
}
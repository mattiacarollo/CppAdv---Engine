#pragma once

#include "GraphicsManager.h"
#include "Utility.h"
#include "ShaderLoader.h"

using namespace utility;
using namespace DirectX;

class Application
{
public:
	Application();

	HRESULT initializeResources(DXManager*,float);
	void preRender();
	void render();
	void cleanResouces();

private:
	ID3D11Buffer* mPVertexBuffer;
	ID3D11Buffer* mPIndexBuffer;
	ID3D11Buffer* mPTranfBuffer;
	ID3D11VertexShader* mPVertexShader;
	ID3D11PixelShader* mPPixelShader;
	ID3D11InputLayout* mPInputLayout;
	ID3D11DepthStencilState* mPDepthStencilState;

	Transformations transf;
	Camera camera;
	DXManager* m_D3D;
};

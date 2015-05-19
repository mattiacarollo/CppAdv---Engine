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

	bool initializeResources(DXManager*,float);
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

	ID3D11RenderTargetView* mRTW;
	DXManager* m_D3D;
	Camera camera;

	Transformations transf;	
};

#pragma once

#include "ApplicationManager.h"
#include "Utility.h"
#include "ShaderLoader.h"

using namespace utility;

class Application
{
public:
	Application();

	bool initializeResources(DXManager*,float, class TerrainClass*, class ColorShaderClass*);
	void preRender();
	void render(DirectX::XMMATRIX&, DirectX::XMMATRIX&, DirectX::XMMATRIX&);
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

	bool result;

	DXManager* m_D3D;	
};

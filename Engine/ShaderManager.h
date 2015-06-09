#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include "TextureShader.h"
#include "ShadowShader.h"
#include "DepthShader.h"
#include "ColorShader.h"
#include "MultiTextureShader.h"


class ShaderManager
{
public:
	ShaderManager();
	ShaderManager(const ShaderManager&);
	~ShaderManager();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();

	bool RenderTextureShader(ID3D11DeviceContext*, int, int, DirectX::XMMATRIX&, DirectX::XMMATRIX&, DirectX::XMMATRIX&, ID3D11ShaderResourceView*);
	bool RenderColorShader(ID3D11DeviceContext*, int, DirectX::XMMATRIX&, DirectX::XMMATRIX&, DirectX::XMMATRIX&);
	bool RenderShadowShader(ID3D11DeviceContext*, int, DirectX::XMMATRIX&, DirectX::XMMATRIX&, DirectX::XMMATRIX&, DirectX::XMMATRIX&, DirectX::XMMATRIX&, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		DirectX::XMFLOAT3, DirectX::XMFLOAT4, DirectX::XMFLOAT4);
	bool RenderDepthShader(ID3D11DeviceContext*, int, DirectX::XMMATRIX&, DirectX::XMMATRIX&, DirectX::XMMATRIX&);
	bool RenderMultiTextureShader(ID3D11DeviceContext*, int, int, DirectX::XMMATRIX&, DirectX::XMMATRIX&, DirectX::XMMATRIX&, ID3D11ShaderResourceView**);

	/*bool RenderLightShader(ID3D11DeviceContext*, int, DirectX::XMMATRIX, DirectX::XMMATRIX, DirectX::XMMATRIX, ID3D11ShaderResourceView*,
		DirectX::XMFLOAT3, DirectX::XMFLOAT4, DirectX::XMFLOAT4, DirectX::XMFLOAT3, DirectX::XMFLOAT4, float);
		*/
	/*bool RenderBumpMapShader(ID3D11DeviceContext*, int, DirectX::XMMATRIX, DirectX::XMMATRIX, DirectX::XMMATRIX, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, DirectX::XMFLOAT3, DirectX::XMFLOAT4);
		*/
private:
	TextureShader* m_TextureShader;
	ColorShaderClass* m_ColorShader;
	ShadowShaderClass* m_ShadowShader;
	DepthShaderClass* m_DepthShader;
	MultiTextureShader* m_MultiTextureShader;
	//LightShaderClass* m_LightShader;
	//BumpMapShaderClass* m_BumpMapShader;
	
};


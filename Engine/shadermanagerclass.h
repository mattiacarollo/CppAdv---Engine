#pragma once

#include <d3d11.h>
#include <DirectXMath.h>


class ShaderManagerClass
{
public:
	ShaderManagerClass();
	ShaderManagerClass(const ShaderManagerClass&);
	~ShaderManagerClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();

	bool RenderTextureShader(ID3D11DeviceContext*, int, DirectX::XMMATRIX, DirectX::XMMATRIX, DirectX::XMMATRIX, ID3D11ShaderResourceView*);

	bool RenderLightShader(ID3D11DeviceContext*, int, DirectX::XMMATRIX, DirectX::XMMATRIX, DirectX::XMMATRIX, ID3D11ShaderResourceView*,
		DirectX::XMFLOAT3, DirectX::XMFLOAT4, DirectX::XMFLOAT4, DirectX::XMFLOAT3, DirectX::XMFLOAT4, float);

	bool RenderBumpMapShader(ID3D11DeviceContext*, int, DirectX::XMMATRIX, DirectX::XMMATRIX, DirectX::XMMATRIX, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, DirectX::XMFLOAT3, DirectX::XMFLOAT4);

private:
	TextureShaderClass* m_TextureShader;
	//LightShaderClass* m_LightShader;
	//BumpMapShaderClass* m_BumpMapShader;
};


#include "ShaderManager.h"


ShaderManager::ShaderManager()
{
	m_TextureShader = 0;
	m_ColorShader = 0;
	m_DepthShader = 0;
	m_ShadowShader = 0;
	m_MultiTextureShader = 0;
	/*m_LightShader = 0;
	m_BumpMapShader = 0;*/
}


ShaderManager::ShaderManager(const ShaderManager& other)
{
}


ShaderManager::~ShaderManager()
{
}


bool ShaderManager::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;


	// Create the texture shader object.
	m_TextureShader = new TextureShader;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the color shader object.
	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)	{ return false; }
	result = m_ColorShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and Initialize  the shadow shader object.
	m_ShadowShader = new ShadowShaderClass;
	if (!m_ShadowShader)	{ return false; }
	result = m_ShadowShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the shadow shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and Initialize the depth shader object.
	m_DepthShader = new DepthShaderClass;
	if (!m_DepthShader)	{ return false; }
	result = m_DepthShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the depth shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and Initialize the multitexture shader object.
	m_MultiTextureShader = new MultiTextureShader;
	if (!m_MultiTextureShader)	{	return false;	}
	result = m_MultiTextureShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the multitexture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	//m_LightShader = new LightShaderClass;
	//if (!m_LightShader)
	//{
	//	return false;
	//}

	//// Initialize the light shader object.
	//result = m_LightShader->Initialize(device, hwnd);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the bump map shader object.
	//m_BumpMapShader = new BumpMapShaderClass;
	//if (!m_BumpMapShader)
	//{
	//	return false;
	//}

	//// Initialize the bump map shader object.
	//result = m_BumpMapShader->Initialize(device, hwnd);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the bump map shader object.", L"Error", MB_OK);
	//	return false;
	//}

	return true;
}


void ShaderManager::Shutdown()
{
	// Release the bump map shader object.
	//if (m_BumpMapShader)
	//{
	//	m_BumpMapShader->Shutdown();
	//	delete m_BumpMapShader;
	//	m_BumpMapShader = 0;
	//}

	//// Release the light shader object.
	//if (m_LightShader)
	//{
	//	m_LightShader->Shutdown();
	//	delete m_LightShader;
	//	m_LightShader = 0;
	//}
	if (m_DepthShader)
	{
		m_DepthShader->Shutdown();
		delete m_DepthShader;
		m_DepthShader = 0;
	}
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}
	if (m_ShadowShader)
	{
		m_ShadowShader->Shutdown();
		delete m_ShadowShader;
		m_ShadowShader = 0;
	}
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}
	if (m_MultiTextureShader)
	{
		m_MultiTextureShader->Shutdown();
		delete m_MultiTextureShader;
		m_MultiTextureShader = 0;
	}
	return;
}


bool ShaderManager::RenderTextureShader(ID3D11DeviceContext* device, int vertexCount, int instanceCount, DirectX::XMMATRIX& worldMatrix, DirectX::XMMATRIX& viewMatrix, DirectX::XMMATRIX& projectionMatrix,
	ID3D11ShaderResourceView* texture)
{
	bool result;
	
	// Render the model using the texture shader.
	result = m_TextureShader->Render(device, vertexCount, instanceCount, worldMatrix, viewMatrix, projectionMatrix, texture);
	if (!result)	{	return false;	}

	return true;
}

bool ShaderManager::RenderColorShader(ID3D11DeviceContext* device, int indexCount, DirectX::XMMATRIX& worldMatrix, DirectX::XMMATRIX& viewMatrix, DirectX::XMMATRIX& projectionMatrix){
	bool result;

	// Render the model using the texture shader.
	result = m_ColorShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix);
	if (!result)	{ return false; }

	return true;
}

bool ShaderManager::RenderShadowShader(ID3D11DeviceContext* device, int indexCount, DirectX::XMMATRIX& worldMatrix, DirectX::XMMATRIX& viewMatrix, DirectX::XMMATRIX& projectionMatrix, DirectX::XMMATRIX& lightViewMatrix, DirectX::XMMATRIX& lightProjectionMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* depthMapTexture,
	DirectX::XMFLOAT3 lightDirection, DirectX::XMFLOAT4 ambientColor, DirectX::XMFLOAT4 diffuseColor)
{
	bool result;

	// Render the model using the texture shader.
	result = m_ShadowShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix, lightProjectionMatrix, texture, depthMapTexture, lightDirection, ambientColor, diffuseColor );
	if (!result)	{ return false; }

	return true;
}

bool ShaderManager::RenderDepthShader(ID3D11DeviceContext* device, int indexCount, DirectX::XMMATRIX& worldMatrix, DirectX::XMMATRIX& viewMatrix, DirectX::XMMATRIX& projectionMatrix){
	bool result;

	// Render the model using the texture shader.
	result = m_DepthShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix);
	if (!result)	{ return false; }

	return true;
}

bool ShaderManager::RenderMultiTextureShader(ID3D11DeviceContext* device, int vertexCount, int instanceCount, DirectX::XMMATRIX& worldMatrix, DirectX::XMMATRIX& viewMatrix, DirectX::XMMATRIX& projectionMatrix, ID3D11ShaderResourceView** texture)
{
	bool result;

	// Render the model using the texture shader.
	result = m_MultiTextureShader->Render(device, vertexCount, instanceCount, worldMatrix, viewMatrix, projectionMatrix, texture);
	if (!result)	{ return false; }

	return true;
}

//bool ShaderManagerClass::RenderLightShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix,
//	ID3D11ShaderResourceView* texture, D3DXVECTOR3 lightDirection, D3DXVECTOR4 ambient, D3DXVECTOR4 diffuse,
//	D3DXVECTOR3 cameraPosition, D3DXVECTOR4 specular, float specularPower)
//{
//	bool result;
//
//
//	// Render the model using the light shader.
//	result = m_LightShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, ambient, diffuse, cameraPosition,
//		specular, specularPower);
//	if (!result)
//	{
//		return false;
//	}
//
//	return true;
//}
//
//
//bool ShaderManagerClass::RenderBumpMapShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix,
//	ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture, D3DXVECTOR3 lightDirection,
//	D3DXVECTOR4 diffuse)
//{
//	bool result;
//
//
//	// Render the model using the bump map shader.
//	result = m_BumpMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, colorTexture, normalTexture, lightDirection, diffuse);
//	if (!result)
//	{
//		return false;
//	}
//
//	return true;
//}

#include "Application.h"

struct SimpleVertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 color;
};

Application::Application() :
	  mPVertexBuffer(nullptr)
	, mPIndexBuffer(nullptr)
	, mPTranfBuffer(nullptr)
	, mPVertexShader(nullptr)
	, mPPixelShader(nullptr)
	, mPInputLayout(nullptr)
	, mPDepthStencilState(nullptr)
	, m_D3D(nullptr)
{
}

void Application::cleanResouces()
{
	if (mPVertexBuffer)		{ mPVertexBuffer->Release(); delete mPVertexBuffer; mPVertexBuffer = 0; }
	if (mPIndexBuffer)		{ mPIndexBuffer->Release(); delete mPIndexBuffer; mPIndexBuffer = 0; }
	if (mPTranfBuffer)		{ mPTranfBuffer->Release(); delete mPTranfBuffer; mPTranfBuffer = 0; }
	if (mPVertexShader)		{ mPVertexShader->Release(); delete mPVertexShader; mPVertexShader = 0; }
	if (mPPixelShader)		{ mPPixelShader->Release(); delete mPPixelShader; mPPixelShader = 0; }
	if (mPInputLayout)		{ mPInputLayout->Release(); delete mPInputLayout; mPInputLayout = 0; }
	if (mPDepthStencilState){ mPDepthStencilState->Release(); delete mPDepthStencilState; mPDepthStencilState = 0; }
	if (mRTW)				{ mRTW->Release(); delete mRTW; mRTW = 0; }
	if (m_D3D)				{ m_D3D->Shutdown(); delete m_D3D; m_D3D = 0; }
}

bool Application::initializeResources(DXManager* D3D, float screenratio, TerrainClass* terrain, ColorShaderClass* colorshader)
{
	m_D3D = D3D;
	mRTW = m_D3D->GetRenderTargetView();

	// Creazione del cubo da renderizzare.
	SimpleVertex vertices[] =
	{
		{ DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
	};

	unsigned int indices[] =
	{
		3, 1, 0,
		2, 1, 3, // Prima faccia cubo

		0, 5, 4,
		1, 5, 0, // Seconda faccia cubo

		3, 4, 7,
		0, 4, 3, // Terza faccia cubo

		1, 6, 5,
		2, 6, 1, // Quarta faccia cubo

		2, 7, 6,
		3, 7, 2, // Quinta faccia cubo

		6, 4, 5,
		7, 4, 6, // Sesta faccia cubo
	};

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	HRESULT result = S_OK;

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(SimpleVertex) * 8;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = vertices;

	// Creiamo il vertex buffer nel device.
	result = m_D3D->GetDevice()->CreateBuffer(&bufferDesc, &initData, &mPVertexBuffer);
	if (FAILED(result))
		return false;
	
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(unsigned int) * 36;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	initData.pSysMem = indices;
	// Creiamo l'index buffer nel device.
	result = m_D3D->GetDevice()->CreateBuffer(&bufferDesc, &initData, &mPIndexBuffer);
	if (FAILED(result))
		return false;

	ID3DBlob* vsBlob = nullptr;
	result = ShaderLoader::vertexPreBuiltLoad(L"./vertexShader.cso", m_D3D->GetDevice(), &mPVertexShader, &vsBlob);	
	if (FAILED(result))
		return false;

	result = ShaderLoader::createInputLayout(vsBlob, m_D3D->GetDevice(), layout, 2, &mPInputLayout);
	if (FAILED(result))
		return false;

	vsBlob->Release();

	result = ShaderLoader::pixelPreBuiltLoad(L"./pixelShader.cso", m_D3D->GetDevice(), &mPPixelShader);
	if (FAILED(result))
		return false;
	
	// Creiamo un constant buffer per passare le matrici agli shaders (al vertex shader).
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(Transformations);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	result = m_D3D->GetDevice()->CreateBuffer(&bufferDesc, nullptr, &mPTranfBuffer);
	if (FAILED(result))
		return false;

	/*D3D11_DEPTH_STENCIL_DESC dsDescON;
	dsDescON.DepthEnable = true;
	dsDescON.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDescON.DepthFunc = D3D11_COMPARISON_LESS;
	dsDescON.StencilEnable = false;

	result = m_D3D->GetDevice()->CreateDepthStencilState(&dsDescON, &mPDepthStencilState);
	if (FAILED(result))
		return false;*/

	return true;
}

void Application::render(DirectX::XMMATRIX& worldMatrix, DirectX::XMMATRIX& viewMatrix, DirectX::XMMATRIX& projectionMatrix)
{
	Transformations trans;
	trans.view = viewMatrix;
	trans.world = worldMatrix;
	trans.projection = projectionMatrix;
	// Aggiorniamo il constant buffer delle trasformazioni
	m_D3D->GetDeviceContext()->UpdateSubresource(mPTranfBuffer, 0, nullptr, &trans, 0, 0);

	//DirectX::XMFLOAT4 clearColor(0.39f, 0.58f, 0.93f, 1.0f);	
	// Settiamo il render target corrente.
	//m_D3D->GetDeviceContext()->OMSetRenderTargets(1, &mRTW, m_D3D->GetDepthStencilView());
	// Pulizia del render target.
	//m_D3D->GetDeviceContext()->ClearRenderTargetView(m_D3D->GetRenderTargetView(), &(clearColor.x));
	// Pulizia del depth buffer
	//m_D3D->GetDeviceContext()->ClearDepthStencilView(m_D3D->GetDepthStencilView(), D3D11_CLEAR_DEPTH, 1.0f, 0);

	// Settiamo l'input layout.
	m_D3D->GetDeviceContext()->IASetInputLayout(mPInputLayout);
	// Settiamo il vertex buffer da renderizzare
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	m_D3D->GetDeviceContext()->IASetVertexBuffers(0, 1, &mPVertexBuffer, &stride, &offset);
	// Settiamo la topologia della nostra geometria.
	m_D3D->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// Settiamo gli shader da utilizzare
	m_D3D->GetDeviceContext()->VSSetShader(mPVertexShader, nullptr, 0);
	m_D3D->GetDeviceContext()->PSSetShader(mPPixelShader, nullptr, 0);

	//Settiamo i constant buffer da utilizzare.
	m_D3D->GetDeviceContext()->VSSetConstantBuffers(0, 1, &mPTranfBuffer);

	//m_D3D->GetDeviceContext()->OMSetDepthStencilState(mPDepthStencilState, 0);

	m_D3D->GetDeviceContext()->IASetIndexBuffer(mPIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	m_D3D->GetDeviceContext()->DrawIndexed(36, 0, 0);

	return;
}

void Application::preRender()
{	

}


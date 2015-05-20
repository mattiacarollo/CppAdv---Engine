#include "DXManager.h"

DXManager::DXManager()
{
	mPSwapChain = 0;
	mPd3dDevice = 0;
	mPd3dDeviceContext = 0;
	mPRenderTargetView = 0;
	mPDepthStencilView = 0;
	pDepthStencil = 0;
	m_depthStencilState = 0;
	m_alphaEnableBlendingState = 0;
	m_alphaDisableBlendingState = 0;
	m_depthDisabledStencilState = 0;
	mMuntisampleCount = 1;
}

DXManager::~DXManager()
{

}

bool DXManager::Initialize(
	int screenWidth,
	int screenHeight,
	bool vsync,
	HWND HWnd,
	bool fullscreen,
	float screenDepth,
	float screenNear
	)
{
	HRESULT hr = S_OK;
	m_vsync_enabled = vsync;
	mHWnd = HWnd;
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;

	hr = initializeDevice(fullscreen);
	if (FAILED(hr))
		return false;

	hr = getVideoCardInfo();
	if (FAILED(hr))
		return false;

	hr = initializeDepthBufferDesc();
	if (FAILED(hr))
		return false;

	hr = initializeDepthStencilDesc();
	if (FAILED(hr))
		return false;
	
	hr = initializeAlphaBlendStateDesc();
	if (FAILED(hr))
		return false;
	
	hr = initializeRenderTarget();
	if (FAILED(hr))
		return false;

	// Setta il viewport
	D3D11_VIEWPORT vp;
	vp.Width = static_cast<float>(mScreenWidth);
	vp.Height = static_cast<float>(mScreenHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	mPd3dDeviceContext->RSSetViewports(1, &vp);

	return true;
}

HRESULT DXManager::initializeDevice(bool fullscreen)
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL featureLevel;
	featureLevel = D3D_FEATURE_LEVEL_11_0;
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1; 
	sd.BufferDesc.Width = mScreenWidth;
	sd.BufferDesc.Height = mScreenHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
	if (m_vsync_enabled)
	{
		sd.BufferDesc.RefreshRate.Numerator = mNumerator;
		sd.BufferDesc.RefreshRate.Denominator = mDenominator;
	}
	else
	{
		sd.BufferDesc.RefreshRate.Numerator = 0;
		sd.BufferDesc.RefreshRate.Denominator = 1;
	}
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; 
	sd.OutputWindow = mHWnd; 
	sd.SampleDesc.Count = mMuntisampleCount; 
	sd.SampleDesc.Quality = 0;
	if (fullscreen)
	{
		sd.Windowed = false;
	}
	else
	{
		sd.Windowed = true;
	}
	sd.Flags = 0;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_REFERENCE,
		D3D_DRIVER_TYPE_SOFTWARE,
	};
	UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex)
	{
		mDriverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(nullptr, mDriverType, nullptr, createDeviceFlags, &featureLevel, 1,
			D3D11_SDK_VERSION, &sd, &mPSwapChain, &mPd3dDevice, nullptr, &mPd3dDeviceContext);
		if (SUCCEEDED(hr))
		{
			if (mDriverType != D3D_DRIVER_TYPE_HARDWARE)
				showWarningMessageBox(L"No hardware Direct3D here.", L"Warning", mHWnd);
			break;
		}
	}
	if (FAILED(hr))
	{
		showErrorMessageBox(L"Device and swap chain creation failed!", L"Error", mHWnd);
		return hr;
	}

	return S_OK;
}

HRESULT DXManager::getVideoCardInfo()
{
	HRESULT result;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	unsigned int numModes, i, stringLength;
	int error;

	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(result))	{ return false; }

	result = factory->EnumAdapters(0, &adapter);
	if (FAILED(result))	{ return false; }

	result = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(result))	{ return false; }

	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(result))	{ return false; }

	displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList)	{ return false; }

	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(result))	{ return false; }

	for (i = 0; i<numModes; i++)
	{
		if (displayModeList[i].Width == (unsigned int)mScreenWidth)
		{
			if (displayModeList[i].Height == (unsigned int)mScreenHeight)
			{
				mNumerator = displayModeList[i].RefreshRate.Numerator;
				mDenominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	result = adapter->GetDesc(&adapterDesc);
	if (FAILED(result))	{ return false; }

	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024); //MB Video Ram

	error = wcstombs_s(&stringLength, m_videoCardDescription, 128, adapterDesc.Description, 128);
	if (error != 0)	{ return false; }

	delete[] displayModeList;
	displayModeList = 0;

	adapterOutput->Release();
	adapterOutput = 0;

	adapter->Release();
	adapter = 0;

	factory->Release();
	factory = 0;
	return S_OK;
}

HRESULT DXManager::initializeRenderTarget()
{
	HRESULT hr = S_OK;
	ID3D11Texture2D* pBackBuffer;
	hr = mPSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
	{
		showErrorMessageBox(L"No backbuffer texture!", L"Error", mHWnd);
		return hr;
	}
	hr = mPd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mPRenderTargetView);
	pBackBuffer->Release();
	pBackBuffer = 0;
	if (FAILED(hr))
	{
		showErrorMessageBox(L"Render target creation failed!", L"Error", mHWnd);
		return hr;
	}	
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;	// Initailze DepthStencilView
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDSV.ViewDimension = (mMuntisampleCount > 1) ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	descDSV.Flags = 0;
	hr = mPd3dDevice->CreateDepthStencilView(pDepthStencil, &descDSV, &mPDepthStencilView);
	if (FAILED(hr))
	{
		showErrorMessageBox(L"Depth-Stencil view creation failed!", L"Error", mHWnd);
		return hr;
	}//END Initialize DepthStencilView
	
	mPd3dDeviceContext->OMSetRenderTargets(1, &mPRenderTargetView, mPDepthStencilView);

	return S_OK;
}

HRESULT DXManager::initializeDepthBufferDesc()
{
	HRESULT hr = S_OK;
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = mScreenWidth;
	descDepth.Height = mScreenHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;;
	descDepth.SampleDesc.Count = mMuntisampleCount;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = mPd3dDevice->CreateTexture2D(&descDepth, nullptr, &pDepthStencil);
	if (FAILED(hr))
	{
		showErrorMessageBox(L"Depth-Stencil buffer creation failed!", L"Error", mHWnd);
		return hr;
	}
	return S_OK;
}

HRESULT DXManager::initializeDepthStencilDesc()
{
	HRESULT hr = S_OK;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	hr = mPd3dDevice->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
	if (FAILED(hr))
	{
		return false;
	}
	mPd3dDeviceContext->OMSetDepthStencilState(m_depthStencilState, 1);
	return S_OK;
}

HRESULT DXManager::initializeAlphaBlendStateDesc()
{
	HRESULT hr = S_OK;
	D3D11_BLEND_DESC blendStateDescription;
	ZeroMemory(&blendStateDescription, sizeof(D3D11_BLEND_DESC));
	blendStateDescription.RenderTarget[0].BlendEnable = TRUE;
	blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].RenderTargetWriteMask = 0x0f;
	hr = mPd3dDevice->CreateBlendState(&blendStateDescription, &m_alphaEnableBlendingState);
	if (FAILED(hr))
	{
		return false;
	}
	blendStateDescription.RenderTarget[0].BlendEnable = FALSE;
	hr = mPd3dDevice->CreateBlendState(&blendStateDescription, &m_alphaDisableBlendingState);
	if (FAILED(hr))
	{
		return false;
	}
	return S_OK;
}

void DXManager::GetVideoCardInfo(char* cardName, int& memory)
{
	strcpy_s(cardName, 128, m_videoCardDescription);
	memory = m_videoCardMemory;
	return;
}

void DXManager::TurnZBufferOn()
{
	mPd3dDeviceContext->OMSetDepthStencilState(m_depthStencilState, 1);
	return;
}

void DXManager::TurnZBufferOff()
{
	mPd3dDeviceContext->OMSetDepthStencilState(m_depthDisabledStencilState, 1);
	return;
}

void DXManager::TurnOnAlphaBlending()
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	mPd3dDeviceContext->OMSetBlendState(m_alphaEnableBlendingState, blendFactor, 0xffffffff);
	return;
}

void DXManager::TurnOffAlphaBlending()
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	mPd3dDeviceContext->OMSetBlendState(m_alphaDisableBlendingState, blendFactor, 0xffffffff);
	return;
}

void DXManager::BeginScene(float red, float green, float blue, float alpha)
{
	float color[4] = { red, green, blue, alpha };
	mPd3dDeviceContext->ClearRenderTargetView(mPRenderTargetView, color);
	mPd3dDeviceContext->ClearDepthStencilView(mPDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	return;
}

void DXManager::EndScene()
{
	if (m_vsync_enabled)	{ mPSwapChain->Present(1, 0); }
	else	{ mPSwapChain->Present(0, 0); }
	return;
}

void DXManager::Shutdown()
{
	if (mPSwapChain)	{ mPSwapChain->Release(); delete mPSwapChain; mPSwapChain = 0; }
	if (mPd3dDevice)	{ mPd3dDevice->Release(); delete mPd3dDevice; mPd3dDevice = 0; }
	if (mPd3dDeviceContext)	{ mPd3dDeviceContext->Release(); delete mPd3dDeviceContext; mPd3dDeviceContext = 0; }
	if (mPRenderTargetView)	{ mPRenderTargetView->Release(); delete mPRenderTargetView; mPRenderTargetView = 0; }
	if (pDepthStencil)	{ pDepthStencil->Release(); delete pDepthStencil; pDepthStencil = 0; }
	if (mPDepthStencilView)	{ mPDepthStencilView->Release(); delete mPDepthStencilView; mPDepthStencilView = 0; }
	if (m_depthStencilState)	{ m_depthStencilState->Release(); delete m_depthStencilState; m_depthStencilState = 0; }
	if (m_alphaEnableBlendingState)	{ m_alphaEnableBlendingState->Release(); delete m_alphaEnableBlendingState; m_alphaEnableBlendingState = 0; }
	if (m_alphaDisableBlendingState)	{ m_alphaDisableBlendingState->Release(); delete m_alphaDisableBlendingState; m_alphaDisableBlendingState = 0; }
	if (m_depthDisabledStencilState)	{ m_depthDisabledStencilState->Release(); delete m_depthDisabledStencilState; m_depthDisabledStencilState = 0; }
}
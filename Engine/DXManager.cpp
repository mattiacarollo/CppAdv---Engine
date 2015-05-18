#include "DXManager.h"

DXManager::DXManager()
{
	mPSwapChain = 0;
	mPd3dDevice = 0;
	mPd3dDeviceContext = 0;
	mPRenderTargetView = 0;
	mPDepthStencilView = 0;
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
	mVSync = vsync;
	mHWnd = HWnd;
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;

	hr = initializeDevice();
	if (FAILED(hr))
		return E_FAIL;

	hr = initializeRenderTarget();
	if (FAILED(hr))
		return E_FAIL;

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

HRESULT DXManager::initializeDevice()
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1; 
	sd.BufferDesc.Width = mScreenWidth;
	sd.BufferDesc.Height = mScreenHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1; 
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; 
	sd.OutputWindow = mHWnd; 
	sd.SampleDesc.Count = mMuntisampleCount; 
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE; 

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
		hr = D3D11CreateDeviceAndSwapChain(nullptr, mDriverType, nullptr, createDeviceFlags, nullptr, 0,
			D3D11_SDK_VERSION, &sd, &mPSwapChain, &mPd3dDevice, nullptr, &mPd3dDeviceContext);
		if (SUCCEEDED(hr))
		{
			if (mDriverType != D3D_DRIVER_TYPE_HARDWARE)
				showWarningMessageBox("No hardware Direct3D here.", "Warning", mHWnd);
			break;
		}
	}
	if (FAILED(hr))
	{
		showErrorMessageBox("Device and swap chain creation failed!", "Error", mHWnd);
		return hr;
	}

	return S_OK;
}

HRESULT DXManager::initializeRenderTarget()
{
	HRESULT hr = S_OK;
	ID3D11Texture2D* pBackBuffer;
	hr = mPSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
	{
		showErrorMessageBox("No backbuffer texture!", "Error", mHWnd);
		return hr;
	}
	hr = mPd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mPRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
	{
		showErrorMessageBox("Render target creation failed!", "Error", mHWnd);
		return hr;
	}
	ID3D11Texture2D* pDepthStencil = nullptr;
	D3D11_TEXTURE2D_DESC descDepth;
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
		showErrorMessageBox("Depth-Stencil buffer creation failed!", "Error", mHWnd);
		return hr;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDSV.ViewDimension = (mMuntisampleCount > 1) ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	descDSV.Flags = 0;
	hr = mPd3dDevice->CreateDepthStencilView(pDepthStencil, &descDSV, &mPDepthStencilView);
	if (FAILED(hr))
	{
		showErrorMessageBox("Depth-Stencil view creation failed!", "Error", mHWnd);
		return hr;
	}
	mPd3dDeviceContext->OMSetRenderTargets(1, &mPRenderTargetView, mPDepthStencilView);

	return S_OK;
}

void DXManager::BeginScene(float red, float green, float blue, float alpha)
{
	float color[4];
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;
	mPd3dDeviceContext->ClearRenderTargetView(mPRenderTargetView, color);
	mPd3dDeviceContext->ClearDepthStencilView(mPDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	return;
}

void DXManager::EndScene()
{
	mPSwapChain->Present(0, 0);
	return;
}

void DXManager::Shutdown()
{
	if (mPSwapChain)	{ mPSwapChain->Release(); mPSwapChain = 0; }	return;
	if (mPd3dDevice)	{ mPd3dDevice->Release(); mPd3dDevice = 0; }	return;	
	if (mPd3dDeviceContext)	{ mPd3dDeviceContext->Release(); mPd3dDeviceContext = 0; }	return;
	if (mPRenderTargetView)	{ mPRenderTargetView->Release(); mPRenderTargetView = 0; }	return;
	if (mPDepthStencilView)	{ mPDepthStencilView->Release(); mPDepthStencilView = 0; }	return;
}
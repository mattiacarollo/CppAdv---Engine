#pragma once

#include <d3d11.h>
#include "Utility.h"

using namespace utility;

class DXManager {
public:
	DXManager();
	DXManager(const DXManager&);
	~DXManager();

	bool Initialize(int,int,bool,HWND,bool,float,float);
	void BeginScene(float, float, float, float);
	void EndScene();
	void Shutdown();

private:
	HRESULT initializeDevice();
	HRESULT initializeRenderTarget();

private:
	ID3D11Device* mPd3dDevice;
	IDXGISwapChain* mPSwapChain;
	ID3D11DeviceContext* mPd3dDeviceContext;
	ID3D11RenderTargetView* mPRenderTargetView;
	ID3D11DepthStencilView* mPDepthStencilView;
	HWND mHWnd;
	D3D_DRIVER_TYPE mDriverType;
	bool mVSync;
	int mScreenWidth;
	int mScreenHeight;
	int mMuntisampleCount;
};
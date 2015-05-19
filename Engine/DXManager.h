#pragma once

#include "Utility.h"

using namespace utility;

class DXManager {
public:
	DXManager();
	DXManager(const DXManager&);
	~DXManager();

	bool Initialize(int, int, bool, HWND, bool, float, float);
	void BeginScene(float, float, float, float);
	void EndScene();
	void Shutdown();

	ID3D11Device* GetDevice() { return mPd3dDevice; }
	IDXGISwapChain* GetSwapChain() { return mPSwapChain; }
	ID3D11DeviceContext* GetDeviceContext() { return mPd3dDeviceContext; }
	ID3D11RenderTargetView* GetRenderTargetView(){ return mPRenderTargetView; }
	ID3D11DepthStencilView* GetDepthStencilView(){ return mPDepthStencilView; }

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
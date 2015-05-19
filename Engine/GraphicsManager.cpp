#include "GraphicsManager.h"

GraphicsManager::GraphicsManager()
{
	m_D3D = 0;
	m_app = 0;
}


GraphicsManager::GraphicsManager(const GraphicsManager& other)
{
}


GraphicsManager::~GraphicsManager()
{
}


bool GraphicsManager::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	float screenratio = screenWidth / screenHeight;
	m_D3D = new DXManager;
	if (!m_D3D) {	return false;	}
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	m_app = new Application;
	if (!m_app) { return false; }
	result = m_app->initializeResources(m_D3D, screenratio);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Application", L"Error", MB_OK);
		return false;
	}
	
	return true;
}


void GraphicsManager::Shutdown()
{
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
	if (m_app)
	{
		m_app->cleanResouces();
		delete m_app;
		m_app = 0;
	}
	
	return;
}


bool GraphicsManager::Frame()
{
	bool result;

	static float rotation = 0.0f;
	rotation += (float)DirectX::XM_PI * 0.005f;
	if (rotation > 360.0f)	{	rotation -= 360.0f;	}

	result = Render(rotation);
	if (!result) {	 return false;	}

	return true;
}


bool GraphicsManager::Render(float rotation)
{
	DirectX::XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;

	m_D3D->BeginScene(0.12f, 0.29f, 0.22f, 0.5f);
	worldMatrix = DirectX::XMMatrixRotationY(rotation);

	m_app->preRender();
	m_app->render();

	
	m_D3D->EndScene();

	return true;
}
#include "GraphicsManager.h"

GraphicsManager::GraphicsManager()
{
	m_D3D = 0;
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
		MessageBox(hwnd, "Could not initialize Direct3D", "Error", MB_OK);
		return false;
	}

	transf.world = XMMatrixScaling(2.0f, 2.0f, 2.0f);
	transf.view = m_Camera.getViewMatrix();
	transf.cameraPosition = m_Camera.getCameraPositionFlaot4();
	transf.projection = XMMatrixPerspectiveFovLH(XMConvertToRadians(45.0f), screenratio, 0.1f, 100.0f);

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
	return;
}


bool GraphicsManager::Frame()
{
	bool result;

	static float rotation = 0.0f;
	rotation += (float)XM_PI * 0.005f;
	if (rotation > 360.0f)	{	rotation -= 360.0f;	}

	result = Render(rotation);
	if (!result) {	 return false;	}

	return true;
}


bool GraphicsManager::Render(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;

	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	worldMatrix = XMMatrixRotationY(rotation);



	
	m_D3D->EndScene();

	return true;
}
//#include "GraphicsManager.h"
//
//GraphicsManager::GraphicsManager()
//{
//	m_D3D = 0;
//	m_app = 0;
//	m_Camera = 0;
//	m_input = 0;
//}
//
//
//GraphicsManager::GraphicsManager(const GraphicsManager& other)
//{
//}
//
//
//GraphicsManager::~GraphicsManager()
//{
//}
//
//
//bool GraphicsManager::Initialize(int screenWidth, int screenHeight, HWND hwnd, InputManager* Input)
//{
//	bool result;
//	float screenratio = static_cast<float>(screenWidth) / (screenHeight);
//	m_input = Input;
//
//	m_D3D = new DXManager;
//	if (!m_D3D) {	return false;	}
//	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
//	if (!result)
//	{
//		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
//		return false;
//	}
//
//	m_app = new Application;
//	if (!m_app) { return false; }
//	result = m_app->initializeResources(m_D3D, screenratio, this);
//	if (!result)
//	{
//		MessageBox(hwnd, L"Could not initialize Application", L"Error", MB_OK);
//		return false;
//	}
//	
//	m_Camera = new Camera;
//	if (!m_Camera) 
//	{
//		MessageBox(hwnd, L"Could not initialize Camera", L"Error", MB_OK);
//		return false;
//	}
//
//	transf.world = DirectX::XMMatrixScaling(2.0f, 2.0f, 2.0f);
//	transf.view = m_Camera->getViewMatrix();
//	transf.cameraPosition = m_Camera->getCameraPositionFlaot4();
//	transf.projection = DirectX::XMMatrixPerspectiveFovLH(XMConvertToRadians(45.0f), screenratio, 0.1f, 100.0f);
//
//	return true;
//}
//
//bool GraphicsManager::Frame()
//{
//	static utility::Timer timer;
//	const float degForSec = 1.0f;
//
//	float fSec = timer.elapsedSecF();
//	XMFLOAT4 viewAxeRotation(0.0f, 0.0f, 0.0f, 0.0f);
//	float viewTraslation = 0.0f;
//
//	if (m_input->IsKeyDown(0x57))		m_Camera->xRotation(-fSec);
//	if (m_input->IsKeyDown(0x41))		m_Camera->yRotation(fSec);
//	if (m_input->IsKeyDown(0x53))		m_Camera->xRotation(fSec);
//	if (m_input->IsKeyDown(0x44))		m_Camera->yRotation(-fSec);
//	if (m_input->IsKeyDown(0x51))		viewTraslation += (2.0f * fSec);
//	if (m_input->IsKeyDown(0x45))		viewTraslation -= (2.0f * fSec);
//
//	if (viewTraslation != 0.0f)		m_Camera->translate(viewTraslation);
//
//	XMFLOAT4 axeRotation(0.0f, 0.0f, 0.0f, 0.0f);
//
//	if (m_input->IsKeyDown(VK_LEFT))	axeRotation.y -= 1.0f;
//	if (m_input->IsKeyDown(VK_RIGHT))	axeRotation.y += 1.0f;
//	if (m_input->IsKeyDown(VK_UP))		axeRotation.x -= 1.0f;
//	if (m_input->IsKeyDown(VK_DOWN))	axeRotation.x += 1.0f;
//
//	if (axeRotation.x != 0.0f || axeRotation.y != 0.0f)
//	{
//		float angle = degForSec * fSec;
//		XMMATRIX rotationMatrix = XMMatrixRotationAxis(XMLoadFloat4(&axeRotation), angle);
//		XMMATRIX newWorldMatrix = XMMatrixMultiply(rotationMatrix, transf.world);
//		transf.world = newWorldMatrix;
//	}
//
//	transf.view = m_Camera->getViewMatrix();
//	transf.cameraPosition = m_Camera->getCameraPositionFlaot4();
//
//	timer.start();
//	bool result;
//	result = Render();
//	if (!result)
//	{
//		return false;
//	}
//	return true;
//}
//
//
//bool GraphicsManager::Render()
//{
//	m_D3D->BeginScene(0.12f, 0.29f, 0.60f, 0.5f);
//
//	m_app->preRender();
//	m_app->render();
//	
//	m_D3D->EndScene();
//
//	return true;
//}
//
//
//void GraphicsManager::Shutdown()
//{
//	if (m_D3D)
//	{
//		m_D3D->Shutdown();
//		delete m_D3D;
//		m_D3D = 0;
//	}
//	if (m_app)
//	{
//		m_app->cleanResouces();
//		delete m_app;
//		m_app = 0;
//	}
//	if (m_input)
//	{
//		delete m_input;
//		m_input = 0;
//	}
//	if (m_Camera)
//	{
//		delete m_Camera;
//		m_Camera = 0;
//	}
//	return;
//}
#include "GraphicsManager.h"

GraphicsManager::GraphicsManager()
{
	m_Terrain = 0;
	m_ColorShader = 0;
	m_App = 0;
	m_Camera = 0;
}


GraphicsManager::GraphicsManager(const GraphicsManager& other)
{
}


GraphicsManager::~GraphicsManager()
{
}


bool GraphicsManager::Initialize(DXManager* D3D, HWND hwnd, Camera* camera)
{
	m_D3D = D3D;
	m_Camera = camera;
	bool result;
	// Create and Initialize the terrain object.
	m_Terrain = new TerrainClass;
	if (!m_Terrain)	{ return false; }
	result = m_Terrain->Initialize(m_D3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the color shader object.
	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)	{ return false; }
	result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the Application object.
	m_App = new Application;
	if (!m_App)	{ return false; }
	result = m_App->initializeResources(D3D);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Application object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

bool GraphicsManager::Frame()
{
	bool result;
	result = Render();
	if (!result) { return false; }
	return true;
}


bool GraphicsManager::Render()
{
	bool result;
	utility::Transformations trans;
	m_Camera->Render();
	m_Camera->GetViewMatrix(trans.view);
	trans.world = m_D3D->GetTransf()->world;
	trans.projection = m_D3D->GetTransf()->projection;

	m_App->render(trans.world, trans.view, trans.projection);

	m_Terrain->Render(m_D3D->GetDeviceContext());
	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Terrain->GetIndexCount(), trans.world, trans.view, trans.projection);
	if (!result)
	{
		return false;
	}

	return true;
}


void GraphicsManager::Shutdown()
{
	if (m_Terrain)
	{
		delete m_Terrain;
		m_Terrain = 0;
	}
	if (m_ColorShader)
	{
		delete m_ColorShader;
		m_ColorShader = 0;
	}
	if (m_App)
	{
		delete m_App;
		m_App = 0;
	}
	if (m_Camera)
	{
		delete m_App;
		m_App = 0;
	}
	return;
}
#include "GraphicsManager.h"

GraphicsManager::GraphicsManager()
{
	m_Terrain = 0;
	m_ColorShader = 0;
	m_Camera = 0;
	m_CubeModel = 0;
	m_SphereModel = 0;
	m_ShadowShader = 0;
	m_RenderTexture = 0;
	m_Light = 0;
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

	// Create, initialize and set position of the CUBE model object.
	m_CubeModel = new ModelClass;
	if (!m_CubeModel)	{	return false;	}
	result = m_CubeModel->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/wall01.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the cube model object.", L"Error", MB_OK);
		return false;
	}
	m_CubeModel->SetPosition(50.0f, 2.0f, 10.0f);

	// Create, initialize and set position of the SPHERE model object.
	m_SphereModel = new ModelClass;
	if (!m_SphereModel)	{	return false;	}
	result = m_SphereModel->Initialize(m_D3D->GetDevice(), "../Engine/data/sphere.txt", L"../Engine/data/ice.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sphere model object.", L"Error", MB_OK);
		return false;
	}
	m_SphereModel->SetPosition(50.0f, 10.0f, 10.0f);

	// Create and initialize the light object.
	m_Light = new LightClass;
	if (!m_Light)	{	return false;	}
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->GenerateOrthoMatrix(20.0f, SHADOWMAP_DEPTH, SHADOWMAP_NEAR);

	// Create and Initialize  the shadow shader object.
	m_ShadowShader = new ShadowShaderClass;
	if (!m_ShadowShader)	{	return false;	}
	result = m_ShadowShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the shadow shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and Initialize the render to texture object.
	m_RenderTexture = new RenderTextureClass;
	if (!m_RenderTexture)	{	return false;	}
	result = m_RenderTexture->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SHADOWMAP_DEPTH, SHADOWMAP_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create and Initialize the depth shader object.
	m_DepthShader = new DepthShaderClass;
	if (!m_DepthShader)	{	return false;	}
	result = m_DepthShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the depth shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

bool GraphicsManager::Frame(float frameTime)
{
	bool result;
	static float lightAngle = 270.0f;
	float radians;
	static float lightPosX = 9.0f;

	// Update the position of the light each frame.
	lightPosX -= 0.003f * frameTime;

	// Update the angle of the light each frame.
	lightAngle -= 0.03f * frameTime;
	if (lightAngle < 90.0f)
	{
		lightAngle = 270.0f;

		// Reset the light position also.
		lightPosX = 9.0f;
	}
	radians = lightAngle * 0.0174532925f;

	// Update the direction of the light.
	m_Light->SetDirection(sinf(radians), cosf(radians), 0.0f);

	// Set the position and lookat for the light.
	m_Light->SetPosition(lightPosX, 8.0f, -0.1f);
	m_Light->SetLookAt(-lightPosX, 0.0f, 0.0f);

	// Render the graphics scene.
	result = Render();
	if (!result)	{	return false;	}

	return true;
}

bool GraphicsManager::RenderSceneToTexture()
{
	DirectX::XMMATRIX worldMatrix, lightViewMatrix, lightOrthoMatrix;
	float posX, posY, posZ;
	bool result;

	// Set the render target to be the render to texture.
	m_RenderTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_RenderTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the light view matrix based on the light's position.
	m_Light->GenerateViewMatrix();

	// Get the world matrix from the d3d object.
	worldMatrix =m_D3D->GetTransf()->world;

	// Get the view and orthographic matrices from the light object.
	m_Light->GetViewMatrix(lightViewMatrix);
	m_Light->GetOrthoMatrix(lightOrthoMatrix);

	// Setup the translation matrix for the cube model.
	m_CubeModel->GetPosition(posX, posY, posZ);
	worldMatrix = DirectX::XMMatrixTranslation(posX, posY, posZ);

	// Render the cube model with the depth shader.
	m_CubeModel->Render(m_D3D->GetDeviceContext());
	result = m_DepthShader->Render(m_D3D->GetDeviceContext(), m_CubeModel->GetIndexCount(), worldMatrix, lightViewMatrix, lightOrthoMatrix);
	if (!result)
	{
		return false;
	}

	// Reset the world matrix.
	worldMatrix = m_D3D->GetTransf()->world;

	// Setup the translation matrix for the sphere model.
	m_SphereModel->GetPosition(posX, posY, posZ);
	worldMatrix = DirectX::XMMatrixTranslation(posX, posY, posZ);

	// Render the sphere model with the depth shader.
	m_SphereModel->Render(m_D3D->GetDeviceContext());
	result = m_DepthShader->Render(m_D3D->GetDeviceContext(), m_SphereModel->GetIndexCount(), worldMatrix, lightViewMatrix, lightOrthoMatrix);
	if (!result)
	{
		return false;
	}
	// Reset the world matrix.
	worldMatrix = m_D3D->GetTransf()->world;
	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return true;
}

bool GraphicsManager::Render()
{
	bool result;
	utility::Transformations trans;
	DirectX::XMMATRIX lightViewMatrix, lightOrthoMatrix;
	float posX, posY, posZ;

	// First render the scene to a texture.
	result = RenderSceneToTexture();
	if (!result)	{	return false;	}

	m_Camera->Render(); //Render camera
	m_Light->GenerateViewMatrix();

	trans.world = m_D3D->GetTransf()->world;
	m_Camera->GetViewMatrix(trans.view); //Get camera matrix
	trans.projection = m_D3D->GetTransf()->projection;

	m_Light->GetViewMatrix(lightViewMatrix);
	m_Light->GetOrthoMatrix(lightOrthoMatrix);



	//m_Terrain->Render(m_D3D->GetDeviceContext());
	//result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Terrain->GetIndexCount(), trans.world, trans.view, trans.projection);
	//if (!result)
	//{
	//	return false;
	//}

	//return true;




	// Setup the translation matrix for the cube model.
	m_CubeModel->GetPosition(posX, posY, posZ);
	trans.world = DirectX::XMMatrixTranslation(posX, posY, posZ);

	// Put the cube model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_CubeModel->Render(m_D3D->GetDeviceContext());

	// Render the model using the shadow shader.
	result = m_ShadowShader->Render(m_D3D->GetDeviceContext(), m_CubeModel->GetIndexCount(), trans.world, trans.view, trans.projection, lightViewMatrix,
		lightOrthoMatrix, m_CubeModel->GetTexture(), m_RenderTexture->GetShaderResourceView(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	if (!result)	{	return false;	}
	trans.world = m_D3D->GetTransf()->world;

	trans.world = m_D3D->GetTransf()->world;
	// Setup the translation matrix for the sphere model.
	m_SphereModel->GetPosition(posX, posY, posZ);
	trans.world = DirectX::XMMatrixTranslation(posX, posY, posZ);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_SphereModel->Render(m_D3D->GetDeviceContext());
	result = m_ShadowShader->Render(m_D3D->GetDeviceContext(), m_SphereModel->GetIndexCount(), trans.world, trans.view, trans.projection, lightViewMatrix,
		lightOrthoMatrix, m_SphereModel->GetTexture(), m_RenderTexture->GetShaderResourceView(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	if (!result)	{	return false;	}

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
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}
	if (m_CubeModel)
	{
		delete m_CubeModel;
		m_CubeModel = 0;
	}	
	if (m_SphereModel)
	{
		delete m_SphereModel;
		m_SphereModel = 0;
	}
	if (m_ShadowShader)
	{
		delete m_ShadowShader;
		m_ShadowShader = 0;
	}
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}
	if (m_RenderTexture)
	{
		delete m_RenderTexture;
		m_RenderTexture = 0;
	}
	if (m_DepthShader)
	{
		delete m_DepthShader;
		m_DepthShader = 0;
	}
	return;
}
#include "ApplicationManager.h"


ApplicationManager::ApplicationManager()
{
	m_Input = 0;
	m_D3D = 0;
	m_Camera = 0;
	m_App = 0;
	m_Position = 0;
	m_Terrain = 0;
	m_ColorShader = 0;
	m_Timer = 0;
}


ApplicationManager::ApplicationManager(const ApplicationManager& other){}


ApplicationManager::~ApplicationManager(){}


bool ApplicationManager::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;
	float cameraX, cameraY, cameraZ;
	DirectX::XMMATRIX baseViewMatrix;
	float screenratio = static_cast<float>(screenWidth) / (screenHeight);
	
	// Create and Initialize the Input object.
	m_Input = new InputManager;
	if (!m_Input){ return false; }
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize InputKeyboardSetup", L"Error", MB_OK);
		return false;
	}

	// Create and Initialize the DirectX object.
	m_D3D = new DXManager;
	if (!m_D3D) { return false; }
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create and Initialize the Camera object.
	m_Camera = new Camera;
	if (!m_Camera)
	{
		MessageBox(hwnd, L"Could not initialize Camera", L"Error", MB_OK);
		return false;
	}
	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render();
	cameraX = 50.0f;
	cameraY = 2.0f;
	cameraZ = -7.0f;
	m_Camera->SetPosition(cameraX, cameraY, cameraZ);

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
	if (!m_ColorShader)	{	return false;	}
	result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and Initialize the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)	{	return false;	}
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create and Initialize the position object.
	m_Position = new PositionManager;
	if (!m_Position)	{	return false;	}
	m_Position->SetPosition(cameraX, cameraY, cameraZ);

	//Create and Initialize the Application Object.
	m_App = new Application;
	if (!m_App) { return false; }
	result = m_App->initializeResources(m_D3D, screenratio, m_Terrain, m_ColorShader);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Application", L"Error", MB_OK);
		return false;
	}

	return true;
}


void ApplicationManager::Shutdown()
{
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}
	if (m_App)
	{
		m_App->cleanResouces();
		delete m_App;
		m_App = 0;
	}
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}
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
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}
	return;
}


bool ApplicationManager::Frame()
{
	bool result;

	// Read the user input.
	result = m_Input->Frame();
	if (!result)	{	return false;	}

	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsEscapePressed() == true)	{	return false;	}

	m_Timer->Frame();
	static utility::Timer timer;
	const float degForSec = 1.0f;
	float fSec = timer.elapsedSecF();

	// Do the frame input processing.
	result = HandleInput(m_Timer->GetTime());
	if (!result)	{	return false;	}

	// Render the graphics.
	result = RenderGraphics();
	if (!result)	{	return false;	}

	return result;
}


bool ApplicationManager::HandleInput(float frameTime)
{
	bool keyDown, result;
	float posX, posY, posZ, rotX, rotY, rotZ;

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = m_Input->IsLeftPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = m_Input->IsRightPressed();
	m_Position->TurnRight(keyDown);

	keyDown = m_Input->IsUpPressed();
	m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsDownPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = m_Input->IsAPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = m_Input->IsZPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = m_Input->IsPgUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = m_Input->IsPgDownPressed();
	m_Position->LookDownward(keyDown);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	return true;
}


bool ApplicationManager::RenderGraphics()
{
	utility::Transformations temp;
	bool result;
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 0.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	m_Camera->GetViewMatrix(temp.view);
	temp.world = m_D3D->GetTransf()->world;
	temp.projection = m_D3D->GetTransf()->projection;

	m_App->render(temp.world, temp.view, temp.projection);

	m_Terrain->Render(m_D3D->GetDeviceContext());
	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Terrain->GetIndexCount(), temp.world, temp.view, temp.projection);
	if (!result)
	{
		return false;
	}

	m_D3D->EndScene();

	return true;
}

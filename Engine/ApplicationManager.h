#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_


const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


#include "InputManager.h"
#include "DXManager.h"
#include "Camera.h"
#include "Application.h"
#include "PositionManager.h"
#include "timer.h"
#include "TerrainManager.h"
#include "ColorShader.h"
#include "timerManager.h"

class Application;

class ApplicationManager
{
public:
	ApplicationManager();
	ApplicationManager(const ApplicationManager&);
	~ApplicationManager();

	bool Initialize(HINSTANCE, HWND, int, int);
	bool Frame();
	void Shutdown();

private:
	bool HandleInput(float);
	bool RenderGraphics();

private:
	InputManager* m_Input;
	PositionManager* m_Position;
	DXManager* m_D3D;
	Camera* m_Camera;
	Application* m_App;
	TerrainClass* m_Terrain;
	ColorShaderClass* m_ColorShader;
	TimerClass* m_Timer;
};

#endif
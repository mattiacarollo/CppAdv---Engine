#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_


const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


#include "InputManager.h"
#include "DXManager.h"
#include "Camera.h"
#include "GraphicsManager.h"
#include "PositionManager.h"
#include "timerManager.h" 

class Application;
class GraphicsManager;

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
	GraphicsManager* m_Graphic;
	TimerClass* m_Timer;
};

#endif
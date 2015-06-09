#pragma once

const int SCREEN_WIDTH = 1024;
const int  SCREEN_HEIGHT = 768;
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


#include "InputManager.h"
#include "DXManager.h"
#include "Camera.h"
#include "GraphicsManager.h"
#include "PositionManager.h"
#include "Timer.h" 
#include "MyApplication.h"
#include "CPU.h"
#include "FPS.h"

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
	MyApplication* m_Graphic;
	Timer* m_Timer;
	FpsMonitor* m_Fps;
	CpuMonitor* m_Cpu;
};
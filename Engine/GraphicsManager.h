#pragma once

#include "DXManager.h" 
#include "DataType.h"
#include "Camera.h"
#include "Application.h"
#include "InputManager.h"
#include "timer.h"

using namespace utility;

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class Application;

class GraphicsManager
{
public:
	GraphicsManager();
	GraphicsManager(const GraphicsManager&);
	~GraphicsManager();

	bool Initialize(int, int, HWND, InputManager*);
	bool Frame();
	void Shutdown();

	Transformations* GetTransf() { return &transf; }

private:
	bool Render();

private:
	DXManager* m_D3D;
	Camera* m_Camera;
	Application* m_app;
	InputManager* m_input;
	Transformations transf;
};
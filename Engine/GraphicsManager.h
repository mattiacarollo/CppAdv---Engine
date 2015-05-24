#pragma once

#include "TerrainManager.h"
#include "ColorShader.h"
#include "DXManager.h"
#include "Application.h"
#include "Camera.h"

class Application;
class Camera;

class GraphicsManager
{
public:
	GraphicsManager();
	GraphicsManager(const GraphicsManager&);
	~GraphicsManager();

	bool Initialize(DXManager*, HWND, Camera*);
	bool Frame();
	void Shutdown();

private:
	bool Render();

private:
	DXManager* m_D3D;
	TerrainClass* m_Terrain;
	ColorShaderClass* m_ColorShader;
	Application* m_App;

	Camera* m_Camera;
};
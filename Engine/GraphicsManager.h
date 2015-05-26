#pragma once

#include "TerrainManager.h"
#include "ColorShader.h"
#include "ShadowShader.h"
#include "DXManager.h"
#include "Camera.h"
#include "Model.h"
#include "Light.h"
#include "RenderTexture.h"
#include "DepthShader.h"

const int SHADOWMAP_WIDTH = 1024;
const int SHADOWMAP_HEIGHT = 1024;
const float SHADOWMAP_DEPTH = 50.0f;
const float SHADOWMAP_NEAR = 1.0f;

class Application;
class Camera;

class GraphicsManager
{
public:
	GraphicsManager();
	GraphicsManager(const GraphicsManager&);
	~GraphicsManager();

	bool Initialize(DXManager*, HWND, Camera*);
	bool Frame(float);
	void Shutdown();

private:
	bool RenderSceneToTexture();
	bool Render();

private:
	DXManager* m_D3D;
	TerrainClass* m_Terrain;
	ColorShaderClass* m_ColorShader;
	ShadowShaderClass* m_ShadowShader;
	Application* m_App;
	ModelClass* m_CubeModel;
	ModelClass* m_SphereModel;
	LightClass* m_Light;
	Camera* m_Camera;
	RenderTextureClass* m_RenderTexture;
	DepthShaderClass* m_DepthShader;
};
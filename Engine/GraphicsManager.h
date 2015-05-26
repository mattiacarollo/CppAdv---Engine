#pragma once


#include "Terrain.h"
#include "ColorShader.h"
#include "ShadowShader.h"
#include "DXManager.h"
#include "Camera.h"
#include "Model.h"
#include "LightManager.h"
#include "RenderToTexture.h"
#include "DepthShader.h"


const int SHADOWMAP_WIDTH = 1024;
const int SHADOWMAP_HEIGHT = 1024;
const float SHADOWMAP_DEPTH = 50.0f;
const float SHADOWMAP_NEAR = 1.0f;


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
	LightManager* m_Light;
	Terrain* m_Terrain;
	Model* m_CubeModel;
	Model* m_SphereModel;	
	Camera* m_Camera;
	RenderToTexture* m_RenderTexture;
	ColorShaderClass* m_ColorShader;
	ShadowShaderClass* m_ShadowShader;
	DepthShaderClass* m_DepthShader;
};
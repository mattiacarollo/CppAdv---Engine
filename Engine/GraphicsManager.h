#pragma once


#include "LightManager.h"
#include "DXManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

#include "Camera.h"
#include "Model.h"
#include "Terrain.h"
#include "GameObject.h"
#include "Frustum.h"
#include "SceneModelsList.h"

#include "RenderToTexture.h"

#include "textDrawer.h"
#include "Path.h"

#include <vector>


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
	bool Frame(float, int, int);
	void Shutdown();

protected:
	virtual void start() = 0;
	virtual void update(int, XMMATRIX&, XMMATRIX&, XMMATRIX&) = 0;
	GameObject* InstanceGameObject();

private:
	bool RenderSceneToTexture();
	bool Render(float);
	void addWindows(GameObject*);

protected:
	Model* m_CubeModel;
	Model* m_SphereModel;
	ShaderManager* m_ShaderManager;
	TextureManager* m_TextureManager;

	SceneModelsList* m_SceneModelsList;

private:
	DXManager* m_D3D;
	LightManager* m_Light;
	Terrain* m_Terrain;	
	Camera* m_Camera;
	RenderToTexture* m_RenderToTexture;
	Frustum* m_Frustum;
	TextDrawer* m_TextDrawer;
	TextFont* m_ArialFont;
};
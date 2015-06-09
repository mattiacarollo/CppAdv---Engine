#pragma once


#include "LightManager.h"
#include "DXManager.h"
#include "ShaderManager.h"

#include "Camera.h"
#include "Model.h"
#include "Terrain.h"
#include "GameObject.h"
#include "Frustum.h"
#include "ModelList.h"

#include "RenderToTexture.h"

//#include "DepthShader.h"
//#include "MultiTextureShader.h"
//#include "ColorShader.h"
//#include "ShadowShader.h"

#include "textDrawer.h"

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

	virtual void start(){ };
	virtual void update(){ };
	
	void addWindows(GameObject*);

private:
	bool RenderSceneToTexture();
	bool Render(float);

private:
	DXManager* m_D3D;
	LightManager* m_Light;
	ShaderManager* m_ShaderManager;
	Terrain* m_Terrain;
	Model* m_CubeModel;
	Model* m_SphereModel;	
	Camera* m_Camera;
	RenderToTexture* m_RenderToTexture;
	vector<GameObject*> m_ListGameObject;
	Frustum* m_Frustum;
	ModelListClass* m_ModelList;
	TextDrawer* m_TextDrawer;
	TextFont* m_ArialFont;
};
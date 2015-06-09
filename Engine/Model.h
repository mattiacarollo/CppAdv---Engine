#pragma once


#include <d3d11.h>
#include <fstream>
#include <cstdlib>
#include "DataType.h"
#include "TextureManager.h"


using namespace std;


class Model
{
private:

public:
	Model();
	Model(const Model&);
	~Model();

	bool Initialize(ID3D11Device*, char*, WCHAR*, WCHAR*, unsigned int);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	void SetInstanceCount(int instanceCount) { m_instanceCount = instanceCount; };
	int GetVertexCount();
	int GetInstanceCount();
	ID3D11ShaderResourceView** GetTextureArray();

	void SetPosition(float, float, float);
	void GetPosition(float&, float&, float&);

private:
	bool InitializeBuffers(ID3D11Device*, unsigned int);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTextures(ID3D11Device*, WCHAR*, WCHAR*);
	void ReleaseTexture();

	bool LoadModel(char*);
	void ReleaseModel();

private:
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_instanceBuffer;

	int m_vertexCount;
	int m_instanceCount;

	TextureManager* m_TextureArray;
	utility::ModelType* m_model;
	float m_positionX, m_positionY, m_positionZ;
};


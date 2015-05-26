#pragma once


#include <d3d11.h>
#include <fstream>
#include "DataType.h"
#include "textureclass.h"


using namespace std;


class Model
{
private:

public:
	Model();
	Model(const Model&);
	~Model();

	bool Initialize(ID3D11Device*, char*, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

	void SetPosition(float, float, float);
	void GetPosition(float&, float&, float&);

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	bool LoadModel(char*);
	void ReleaseModel();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	utility::ModelType* m_model;
	float m_positionX, m_positionY, m_positionZ;
};


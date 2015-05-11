////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

#include "textureclass.h"

#include <fstream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
//As stated previously the ModelClass is responsible for encapsulating the geometry for 3D models. In this tutorial we will manually setup the data for a single green triangle. 
//We will also create a vertex and index buffer for the triangle so that it can be rendered.
class ModelClass
{
private:
	//Here is the definition of our vertex type that will be used with the vertex buffer in this ModelClass. 
	//Also take note that this typedef must match the layout in the ColorShaderClass.
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	//The functions here handle initializing and shutdown of the model's vertex and index buffers. 
	bool Initialize(ID3D11Device*, char*, WCHAR*);
	void Shutdown();	
	//The Render function puts the model geometry on the video card to prepare it for drawing by the color shader.
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

	ID3D11ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	bool LoadModel(char*);
	void ReleaseModel();

	//The private variables in the ModelClass are the vertex and index buffer as well as two integers to keep track of the size of each buffer. 
	//Note that all DirectX 11 buffers generally use the generic ID3D11Buffer type and are more clearly identified by a buffer description when they are first created.
private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	ModelType* m_model;
};

#endif
#pragma once

class Model
{

public:
	Model();
	~Model();

	//The functions here handle initializing and shutdown of the model's vertex and index buffers and model name
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
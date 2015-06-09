#pragma once


#include "DDSTextureLoader.h"


class TextureManager
{
public:
	TextureManager();
	TextureManager(const TextureManager&);
	~TextureManager();

	bool Initialize(ID3D11Device*, WCHAR*, WCHAR*);
	void Shutdown();

	ID3D11ShaderResourceView** GetTextureArray();

private:
	ID3D11ShaderResourceView* m_textures[2]; // Solo 2 texture al momento
};


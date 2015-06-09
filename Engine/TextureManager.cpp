#include "TextureManager.h"


TextureManager::TextureManager()
{
	m_textures[0] = 0;
	m_textures[1] = 0;
}


TextureManager::TextureManager(const TextureManager& other)
{
}


TextureManager::~TextureManager()
{
}


bool TextureManager::Initialize(ID3D11Device* device, WCHAR* filename1, WCHAR* filename2)
{
	HRESULT result;
	// Load the first texture in.
	result = DirectX::CreateDDSTextureFromFile(device, filename1, nullptr, &m_textures[0]);
	if (FAILED(result))
	{
		return false;
	}

	// Load the second texture in.
	result = DirectX::CreateDDSTextureFromFile(device, filename2, nullptr, &m_textures[1]);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}


void TextureManager::Shutdown()
{
	if (m_textures[0])
	{
		m_textures[0]->Release();
		m_textures[0] = 0;
	}

	if (m_textures[1])
	{
		m_textures[1]->Release();
		m_textures[1] = 0;
	}

	return;
}


ID3D11ShaderResourceView** TextureManager::GetTextureArray()
{
	return m_textures;
}
#include "GameObject.h"

GameObject::GameObject(TextureManager* textureManager, ShaderManager* shaderManager)
{
	m_TextureManager = textureManager;
	m_ShaderManager = shaderManager;
};

GameObject::~GameObject()
{
}

void GameObject::addTexture(const WCHAR* textureId)
{
	m_textures.push_back(m_TextureManager->GetTexture(textureId));
}

bool GameObject::render(XMMATRIX& worldMatrix, XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix)
{
	bool result;
	switch (m_idShader){
	case color:
	{
		m_idModel->Render();
		result = m_ShaderManager->RenderColorShader(m_idModel->GetVertexCount(), m_idModel->GetInstanceCount(), worldMatrix, viewMatrix, projectionMatrix);
		if (!result)	{ return false; }
	}
		break;
	case depth :
	{
		m_idModel->Render();
		result = m_ShaderManager->RenderDepthShader(m_idModel->GetVertexCount(), m_idModel->GetInstanceCount(), worldMatrix, viewMatrix, projectionMatrix);
		if (!result)	{ return false; }
	}
		break;
	case texture :
	{
		/*m_idModel->Render();
		result = m_ShaderManager->RenderMultiTextureShader(m_idModel->GetVertexCount(), m_idModel->GetInstanceCount(), worldMatrix, viewMatrix, projectionMatrix, this->m_textures);
		if (!result)	{ return false; }*/
	}
		break;
	case shadow :
	{
		/*m_idModel->Render();
		result = m_ShaderManager->RenderShadowShader(m_idModel->GetVertexCount(), m_idModel->GetInstanceCount(), worldMatrix, viewMatrix, projectionMatrix);
		if (!result)	{ return false; }*/
	}
		break;
	case simple :
		break;
	default:
		break;
	}
}

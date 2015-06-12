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

Vector3 GameObject::SphereInertia(float mass, float radius)
{
	//inertia moment of full sphere (I = 2/5 * (m*r^2))
	float inertia = 2 * mass*radius*radius / 5;
	return Vector3(inertia, inertia, inertia);
}

void GameObject::AddRigidBody()
{
	m_pRigidbody = new RigidBody(Vector3(40.f, 5.f, 50.f), 0, 100.0f, SphereInertia(100.0f, 5.0f));

	SphereCollider* sC0 = new SphereCollider(m_pRigidbody->GetPosition(), 5.0);
	m_pRigidbody->AttachCollider(sC0);
	m_pRigidbody->SetColliderType(RigidBody::ColliderTypeEnum::SPHERE);
	
	//rBSphere0->ApplyForce(Vector3(1.0f, 0.0f, 0.0f), Vector3(1.0f, 3.0f, 4.0f));
}

RigidBody& GameObject::GetRigidbody() const
{
	return *m_pRigidbody;
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

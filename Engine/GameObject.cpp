#include "GameObject.h"

GameObject::GameObject(TextureManager* textureManager, ShaderManager* shaderManager)
{	
	m_TextureManager = textureManager;
	m_ShaderManager = shaderManager;
	m_position = {0.0f , 0.0f, 0.0f};
};

GameObject::~GameObject()
{
}

void GameObject::setPosition(float x, float y, float z)
{
	m_position = { x, y, z };
	if (isRigidBody() == true){
		m_pRigidbody->SetPosition(m_position);
	}
}


Vector3 GameObject::SphereInertia(float mass, float radius)
{
	//inertia moment of full sphere (I = 2/5 * (m*r^2))
	float inertia = 2 * mass*radius*radius / 5;
	return Vector3(inertia, inertia, inertia);
}

void GameObject::addRigidBody()
{
	m_pRigidbody = new RigidBody(Vector3(this->getPosition().x, this->getPosition().y, this->getPosition().z), 0, 100.0f, SphereInertia(100.0f, 5.0f));

	SphereCollider* sC0 = new SphereCollider(m_pRigidbody->GetPosition(), 5.0);
	m_pRigidbody->AttachCollider(sC0);
	m_pRigidbody->SetColliderType(RigidBody::ColliderTypeEnum::SPHERE);

	m_position = m_pRigidbody->GetPosition();
	
	m_pRigidbody->ApplyForce(Vector3(1.0f, 0.0f, 0.0f), Vector3(1.0f, 3.0f, 4.0f));
}


bool GameObject::isRigidBody() const
{
	if (m_pRigidbody == nullptr){
		return false;
	}
	else{
		return true;
	}
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
		m_idModel->Render();
		if (m_textures.size() == 1){
			result = m_ShaderManager->RenderTextureShader(m_idModel->GetVertexCount(), m_idModel->GetInstanceCount(), worldMatrix, viewMatrix, projectionMatrix, m_textures.at(0));
		}
		else if (m_textures.size() == 0){
			result = m_ShaderManager->RenderColorShader(m_idModel->GetVertexCount(), m_idModel->GetInstanceCount(), worldMatrix, viewMatrix, projectionMatrix);
		}
		else {
			result = m_ShaderManager->RenderMultiTextureShader(m_idModel->GetVertexCount(), m_idModel->GetInstanceCount(), worldMatrix, viewMatrix, projectionMatrix, m_textures.data());
		}
		if (!result)	{ return false; }
	}
		break;
	default:
		break;
	}
}


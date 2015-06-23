#include "GameObject.h"

unsigned int GameObject::m_IdCount = 0;

GameObject::GameObject(TextureManager* textureManager, ShaderManager* shaderManager)
{	
	
	m_Id = m_IdCount; 
	GameObject::m_IdCount++;
	m_radius = 1.f;
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


void GameObject::addRigidBody(int type, float mass)
{
	Vector3 inertia;
	if (type == 0)
	{
		inertia = Pns::Forces::SphereInertia(mass, m_radius);
	}
	else
	{
		inertia = Pns::Forces::CubeInertia(mass, 10.f, 10.f, 10.f);
	}
	m_pRigidbody = new RigidBody(Vector3(m_position.getX(), m_position.getY(), m_position.getZ()), GameObject::m_Id, mass, inertia);
	
	SphereCollider* sC0 = new SphereCollider(m_pRigidbody->GetPosition(), m_radius);
	m_pRigidbody->AttachCollider(sC0);
	m_pRigidbody->SetColliderType(RigidBody::ColliderTypeEnum::SPHERE);
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
		m_Model->Render();
		result = m_ShaderManager->RenderColorShader(m_Model->GetVertexCount(), m_Model->GetInstanceCount(), worldMatrix, viewMatrix, projectionMatrix);
		if (!result)	{ return false; }
	}
		break;
	case depth :
	{
		m_Model->Render();
		result = m_ShaderManager->RenderDepthShader(m_Model->GetVertexCount(), m_Model->GetInstanceCount(), worldMatrix, viewMatrix, projectionMatrix);
		if (!result)	{ return false; }
	}
		break;
	case texture :
	{
		m_Model->Render();
		if (m_textures.size() == 1){
			result = m_ShaderManager->RenderTextureShader(m_Model->GetVertexCount(), m_Model->GetInstanceCount(), worldMatrix, viewMatrix, projectionMatrix, m_textures.at(0));
		}
		else if (m_textures.size() == 0){
			result = m_ShaderManager->RenderColorShader(m_Model->GetVertexCount(), m_Model->GetInstanceCount(), worldMatrix, viewMatrix, projectionMatrix);
		}
		else {
			result = m_ShaderManager->RenderMultiTextureShader(m_Model->GetVertexCount(), m_Model->GetInstanceCount(), worldMatrix, viewMatrix, projectionMatrix, m_textures.data());
		}
		if (!result)	{ return false; }
	}
		break;
	default:
		break;
	}
}


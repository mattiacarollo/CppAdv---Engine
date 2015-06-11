#include "GameObject.h"

GameObject::GameObject()
{
};

GameObject::~GameObject()
{
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

//switch (idModel)
//{
//case cube:
//	break;
//case sphere:
//	break;
//default:
//	break;
//}

//switch (shaderId)
//{
//case color:
//	break;
//case texture:
//	break;
//default:
//	break;
//}
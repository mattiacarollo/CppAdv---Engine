#include "SphereCollider.h"

/*const int SphereCollider::mk_iSphereColliderType = ColliderType::TypeIndex::SPHERE;

SphereCollider::SphereCollider(const Vector3& pos, const Vector3& displ, float radius)
:Collider(mk_iSphereColliderType, displ), m_fRadius(radius)
		{
		SetPosition(pos);
		};*/

//TO DO: controlla che la pos sia al centro dell'object
SphereCollider::SphereCollider(const Vector3& pos, float radius) 
: Collider(), m_fRadius(radius)
{
	SetPosition(pos);
};

float SphereCollider::GetRadius() const
{
	return m_fRadius;
}
/*
const int SphereCollider::getType()
{
	return SphereCollider::mk_iSphereColliderType;
};*/
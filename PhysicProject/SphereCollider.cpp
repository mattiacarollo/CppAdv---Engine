#include "SphereCollider.h"

SphereCollider::SphereCollider(const Vector3& pos, float radius)
:Collider(), m_fRadius(radius)
{
	SetPosition(pos);
};

float SphereCollider::GetRadius() const
{
	return m_fRadius;
}
#include "Collider.h"

Collider::Collider()
{
};

const Vector3 Collider::GetWorldPosition() const
{
	return *(mk_vPosition);
}

void Collider::SetPosition(const Vector3& Pos)
{
	mk_vPosition = &Pos;
}

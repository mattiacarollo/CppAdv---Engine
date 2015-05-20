#include "Collider.h"

/*
Collider::Collider(int type, const Vector3& displ) : m_iType(type), m_vDisplacement(displ)
{
};*/

Collider::Collider()
{
}

const Vector3 Collider::GetWorldPosition() const
{
	return *(mk_vPosition)+m_vDisplacement;
}

int Collider::GetType() const
{
	return m_iType;
};

void Collider::SetPosition(const Vector3& Pos)
{
	mk_vPosition = &Pos;
}

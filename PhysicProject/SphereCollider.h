#pragma once

#include "Collider.h"

class SphereCollider : public Collider
{

public:
	SphereCollider(const Vector3& pos, float radius);
	float GetRadius() const;

private:
	float m_fRadius;
};
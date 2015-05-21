#pragma once

#include "Collider.h"

class RigidBody;
class SphereCollider : public Collider
{

public:
	//SphereCollider(const Vector3& pos, const Vector3& displ, float radius);
	SphereCollider(const Vector3& pos, float radius);
	float GetRadius() const;

private:
	float m_fRadius;
};
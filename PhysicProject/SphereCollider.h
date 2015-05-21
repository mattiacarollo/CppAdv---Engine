#pragma once

#include "Collider.h"
//#include "ColliderUtil.h"

class RigidBody;
class SphereCollider : Collider
{

public:
	//SphereCollider(const Vector3& pos, const Vector3& displ, float radius);
	SphereCollider(const Vector3& pos, float radius);
	float GetRadius() const;
	//static const int getType();

private:
	float m_fRadius;
	//static const int mk_iSphereColliderType;
};
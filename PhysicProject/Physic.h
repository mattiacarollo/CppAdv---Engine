#pragma once

#include <vector>
#include "Vector3.h"
#include "RigidBody.h"
#include "CollisionType.h"

class CollisionType;

typedef std::vector<RigidBody*> RigidBodyList;
typedef std::vector<int> RigidBodyID;

class Physic
{
public:
	Physic();
	~Physic();

	void ComputePhysic();
	void AddRigidBody(RigidBody& rigidbody, int id);
	void ApplyForce(int id, const Vector3& force, const Vector3& pointOfApplication);
	void DeleteRigidBody(int id);

	static const float mk_fDeltaTime;
	static const Vector3 mk_vGravity;

private:
	Physic(const Physic& other);
	Physic& operator=(const Physic& other);

	RigidBodyID m_RigidBodyID;
	RigidBodyList m_RigidBodyList;

	CollisionType* m_CollisionType;
};
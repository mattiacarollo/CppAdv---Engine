#pragma once

#include <vector>
#include "RigidBody.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "Collision.h"

//class RigidBody;
//class Collision;

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

	bool CollisionDetection(Collider* colliderRb0, Collider* colliderRb1);
	void ResolveCollision(RigidBody& rigidbody0, RigidBody& rigidbody1, Collider* colliderRb0, Collider* colliderRb1);

	static const float mk_fDeltaTime;
	static const Vector3 mk_vGravity;

private:
	Physic(const Physic& other);
	Physic& operator=(const Physic& other);

	RigidBodyID m_RigidBodyID;
	RigidBodyList m_RigidBodyList;

	Collision* m_Collision;
};
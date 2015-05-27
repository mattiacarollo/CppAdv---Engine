#pragma once

#include <vector>
#include "Vector3.h"
#include "RigidBody.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Collision.h"

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

	bool CollisionDetectionSphereSphere(Collider* colliderRb0, Collider* colliderRb1);
	bool CollisionDetectionBoxBox(Collider* colliderRb0, Collider* colliderRb1);
	bool CollisionDetectionBoxSphere(Collider* colliderRb0, Collider* colliderRb1);
	void ResolveCollisionSphereSphere(RigidBody& rigidbody0, RigidBody& rigidbody1, Collider* colliderRb0, Collider* colliderRb1);
	void ResolveCollisionBoxBox(RigidBody& rigidbody0, RigidBody& rigidbody1, Collider* colliderRb0, Collider* colliderRb1);
	void ResolveCollisionBoxSphere(RigidBody& rigidbody0, RigidBody& rigidbody1, Collider* colliderRb0, Collider* colliderRb1);

	bool bo(Collider* colliderRb, Vector3 SecondBoxCenterInFirstBoxSystem, Vector3 SecondHalfSizeInFistSystem, Vector3 Min, Vector3 Max);

	static const float mk_fDeltaTime;
	static const Vector3 mk_vGravity;

private:
	Physic(const Physic& other);
	Physic& operator=(const Physic& other);

	RigidBodyID m_RigidBodyID;
	RigidBodyList m_RigidBodyList;

	Collision* m_Collision;
	float m_fCompenetration;
};
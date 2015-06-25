#pragma once

#include "Collision.h"
#include "RigidBody.h"
//#include "Matrix.h"
#include "Vector3.h"

class RigidBody;
class Collision;
class CollisionDetector
{
public:
	CollisionDetector();

	bool CollisionDetectionSpherePlane(RigidBody& rigidbody0);
	bool CollisionDetectionCubePlane(RigidBody& rigidbody0);
	void ResolveCollisionSpherePlane(RigidBody& rigidbody0, float k, float l, float m);
	void ResolveCollisionCubePlane(RigidBody& rigidbody0, float k, float l, float m);

	bool CollisionDetectionSphereSphere(RigidBody& rigidbody0, RigidBody& rigidbody1);
	bool CollisionDetectionBoxBox(RigidBody& rigidbody0, RigidBody& rigidbody1);
	bool CollisionDetectionBoxSphere(RigidBody& rigidbody0, RigidBody& rigidbody1);

	void ResolveCollisionSphereSphere(RigidBody& rigidbody0, RigidBody& rigidbody1, float k, float l, float m);
	void ResolveCollisionBoxBox(RigidBody& rigidbody0, RigidBody& rigidbody1, float k, float l, float m);
	void ResolveCollisionBoxSphere(RigidBody& rigidbody0, RigidBody& rigidbody1, float k, float l, float m);

private:
	~CollisionDetector();
	CollisionDetector(const CollisionDetector& other);
	CollisionDetector& operator=(const CollisionDetector& other);

	Collision* m_Collision;
};
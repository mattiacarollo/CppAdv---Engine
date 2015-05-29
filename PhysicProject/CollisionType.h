#pragma once

#include "Collision.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "RigidBody.h"
#include "Matrix.h"
#include "Vector3.h"

class CollisionType
{
public:
	CollisionType();
	~CollisionType();

	bool CollisionDetectionSphereSphere(Collider* colliderRb0, Collider* colliderRb1);
	bool CollisionDetectionBoxBox(Collider* colliderRb0, Collider* colliderRb1);
	bool CollisionDetectionBoxSphere(Collider* colliderRb0, Collider* colliderRb1);

	void ResolveCollisionSphereSphere(RigidBody& rigidbody0, RigidBody& rigidbody1, Collider* colliderRb0, Collider* colliderRb1);
	void ResolveCollisionBoxBox(RigidBody& rigidbody0, RigidBody& rigidbody1, Collider* colliderRb0, Collider* colliderRb1);
	void ResolveCollisionBoxSphere(RigidBody& rigidbody0, RigidBody& rigidbody1, Collider* colliderRb0, Collider* colliderRb1);

	bool CheckCollisionBoxVertex(Collider* colliderRb, Vector3 SecondBoxCenterInFirstBoxSystem, Vector3 SecondHalfSizeInFistSystem, Vector3 Min, Vector3 Max);

private:
	CollisionType(const CollisionType& other);
	CollisionType& operator=(const CollisionType& other);

	Collision* m_Collision;
	float m_fCompenetration;

	//attribute for box-box collision
	Vector3 m_vBoxCentersDistance;
	Vector3 m_vBoxVertex[8];
	unsigned int m_iPointsInside;
	int m_aBoxIndexes[8];
	float m_aBoxCompenetration[8];
};
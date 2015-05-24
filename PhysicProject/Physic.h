#pragma once

#include <vector>
//#include "CollisionHandler.h"
//#include "Dispatcher.h"
//#include "CollisionAlgorithms.h"
#include "RigidBody.h"
#include "Collider.h"

class RigidBody;

//typedef CollisionHandler<20> PhysicCollisionHandler;
typedef std::vector<RigidBody*> RigidBodyList;
typedef std::vector<Collider*> ColliderList;
//typedef Dispatcher<Collider, CollidersType, Collision*> ColliderDispatcher;
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
	void AddCollider(Collider* col);

	static const float mk_fDeltaTime;
	static const Vector3 mk_vGravity;

private:
	Physic(const Physic& other);
	Physic& operator=(const Physic& other);

	//PhysicCollisionHandler m_CollisionHandler;
	RigidBodyID m_RigidBodyID;
	RigidBodyList m_RigidBodyList;
	ColliderList m_ColliderList;
	//ColliderDispatcher m_ColliderDispatcher;
};
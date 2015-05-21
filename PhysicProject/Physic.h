#pragma once


#include "Vector3.h"
#include "Matrix.h"

class Physic
{
public:
static void DoPhysic(float deltaTime, Vector3& m_vPos, Vector3& m_vVel, Vector3& m_vG, float M);

private:

};
/*
#include <vector>
//#include "CollisionHandler.h"
//#include "Dispatcher.h"
//#include "ColliderUtil.h"


//typedef ColliderType::ColliderTypeList CollidersType;
//typedef CollisionHandler<20> PhysicCollisionHandler;
typedef std::vector<RigidBody*> RigidBodyList;
typedef std::vector<Collider*> ColliderList;
//typedef Dispatcher<Collider, CollidersType, Collision*> ColliderDispatcher;
typedef std::vector<int> RigidBodyID;
class RigidBody;
class Physics
{

public:
	Physics();
	~Physics();

	void ComputePhysic();
	void AddRigidBody(RigidBody& rigidbody, int id);
	void ApplyForce(int id, const Vector3& force, const Vector3& pointOfApplication);
	void DeleteRigidBody(int id);
	void AddCollider(Collider* col);

	static const float mk_fDeltaTime;
	static const Vector3 mk_vGravity;

private:
	Physics(const Physics& other);
	Physics& operator=(const Physics& other);

	//PhysicCollisionHandler m_CollisionHandler;
	RigidBodyID m_RigidBodyID;
	RigidBodyList m_RigidBodyList;
	ColliderList m_ColliderList;
	//ColliderDispatcher m_ColliderDispatcher;
};*/
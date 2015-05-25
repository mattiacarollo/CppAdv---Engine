#include "Physic.h"

const float Physic::mk_fDeltaTime = 0.025f;
const Vector3 Physic::mk_vGravity = Vector3( 0.0f, -9.8f, 0.0f );

Physic::Physic()
{/*
	m_ColliderDispatcher.Add<BoxCollider, BoxCollider>(CollisionAlgorithm::CollisionDetectionAlgorithm<BoxCollider, BoxCollider>::Fire);
	m_ColliderDispatcher.Add<BoxCollider, SphereCollider>(CollisionAlgorithm::CollisionDetectionAlgorithm<BoxCollider, SphereCollider>::Fire<BoxCollider, SphereCollider>);
	m_ColliderDispatcher.Add<SphereCollider, BoxCollider>(CollisionAlgorithm::CollisionDetectionAlgorithm<BoxCollider, SphereCollider>::Fire<SphereCollider, BoxCollider>);
	m_ColliderDispatcher.Add<SphereCollider, SphereCollider>(CollisionAlgorithm::CollisionDetectionAlgorithm<SphereCollider, SphereCollider>::Fire);*/
}

Physic::~Physic()
{
	unsigned int i;

	for (i = 0; i < m_ColliderList.size(); ++i)
	{
		delete m_ColliderList[i];
	}
	m_ColliderList.clear();

	for (i = 0; i < m_RigidBodyList.size(); ++i)
	{
		delete m_RigidBodyList[i];
	}
	m_RigidBodyList.clear();
	m_RigidBodyID.clear();
}

void Physic::ComputePhysic()
{
	unsigned int i, i2;
	bool MaxCollisionReached = false;

	/*for (i = 0; i < m_RigidBodyList.size(); ++i)
	{
		m_RigidBodyList[i]->DoPhysic(Physic::mk_fDeltaTime);
	}*/
	
	m_RigidBodyList[0]->DoPhysicMove(Physic::mk_fDeltaTime);
	m_RigidBodyList[1]->DoPhysicJump(Physic::mk_fDeltaTime);
	
	
	for (i = 0; i < m_RigidBodyList.size() && !MaxCollisionReached; ++i)
	{
		for (i2 = i + 1; i2 < m_RigidBodyList.size() && !MaxCollisionReached; ++i2)
		{
			MaxCollisionReached = m_CollisionHandler.AddCollision(m_ColliderDispatcher.Dispatch(*(m_RigidBodyList[i]->GetCollider()), *(m_RigidBodyList[i2]->GetCollider())), m_RigidBodyList[i], m_RigidBodyList[i2]);
		}
	}
	m_CollisionHandler.HandleCollision();
}

void Physic::AddRigidBody(RigidBody& rigidbody, int id)
{
	m_RigidBodyID.push_back(id);
	m_RigidBodyList.push_back(&rigidbody);
}

void Physic::ApplyForce(int id, const Vector3& force, const Vector3& pointOfApplication)
{
	bool found = false;
	unsigned int i = 0;

	for (; i < m_RigidBodyID.size() && !found; ++i)
	{
		found = m_RigidBodyID[i] == id;
	}
	if (found)
	{
		m_RigidBodyList[i]->ApplyForce(force, pointOfApplication);
	}
}

//MAYBE NON SENSE
void Physic::DeleteRigidBody(int id)
{
	bool found = false;
	unsigned int i = 0;

	for (; i < m_RigidBodyID.size() && !found; ++i)
	{
		found = m_RigidBodyID[i] == id;
	}

	if (found)
	{
		//TO DO
	}
}

void Physic::AddCollider(Collider* col)
{
	m_ColliderList.push_back(col);
}
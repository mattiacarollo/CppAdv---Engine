#include "Physic.h"

const float Physic::mk_fDeltaTime = 0.025f;
const Vector3 Physic::mk_vGravity = Vector3( 0.0f, -9.8f, 0.0f );

Physic::Physic()
{
}

Physic::~Physic()
{
	unsigned int i;

	for (i = 0; i < m_RigidBodyList.size(); ++i)
	{
		delete m_RigidBodyList[i];
	}
	m_RigidBodyList.clear();
	m_RigidBodyID.clear();
}

void Physic::ComputePhysic()
{
	unsigned int i, j;

	/*for (i = 0; i < m_RigidBodyList.size(); ++i)
	{
		m_RigidBodyList[i]->DoPhysic(Physic::mk_fDeltaTime);
	}*/
	
	m_RigidBodyList[0]->DoPhysicMove(Physic::mk_fDeltaTime, 1.0f);
	m_RigidBodyList[1]->DoPhysicMove(Physic::mk_fDeltaTime, -1.0f);
	//m_RigidBodyList[1]->DoPhysicJump(Physic::mk_fDeltaTime);

	for (i = 0; i < m_RigidBodyList.size(); ++i)
	{
		//second loop not check a rigidbody with itself and previous rigidbody (double check)
		for (j = i + 1; j < m_RigidBodyList.size(); ++j)
		{
			if (CollisionDetection(m_RigidBodyList[i]->GetCollider(), m_RigidBodyList[j]->GetCollider()))
			{
				ResolveCollision(
					*m_RigidBodyList[i], 
					*m_RigidBodyList[j], 
					m_RigidBodyList[i]->GetCollider(), 
					m_RigidBodyList[j]->GetCollider()
				);
			}
		}
	}
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

bool Physic::CollisionDetection(Collider* colliderRb0, Collider* colliderRb1)
{
	// Calculate squared distance between centers
	Vector3 centersDistance = colliderRb0->GetWorldPosition() - colliderRb1->GetWorldPosition();
	float distance = VectorOp::DotProduct(centersDistance, centersDistance);

	// Spheres intersect if squared distance is less than squared sum of radii
	float radiusSum = ((SphereCollider*)colliderRb0)->GetRadius() + ((SphereCollider*)colliderRb1)->GetRadius();
	float sqrRadius = radiusSum * radiusSum;
	
	if (distance <= sqrRadius)
	{
		return true;
	}

	return false;
}


void Physic::ResolveCollision(RigidBody& rigidbody0, RigidBody& rigidbody1, Collider* colliderRb0, Collider* colliderRb1)
{
	Vector3 force = rigidbody0.GetVelocity() + rigidbody1.GetVelocity();

	Vector3 centersDistance = colliderRb0->GetWorldPosition() - colliderRb1->GetWorldPosition();
	centersDistance.Normalize();
	Vector3 poa = centersDistance * ((SphereCollider*)colliderRb0)->GetRadius();

	m_Collision = new Collision(&rigidbody0, &rigidbody1, poa, force, centersDistance);
	m_Collision->ApplyCollision();
}
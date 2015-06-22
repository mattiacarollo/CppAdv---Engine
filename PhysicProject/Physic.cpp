#include "Physic.h"

const float Physic::mk_fDeltaTime = 0.025f;
const Vector3 Physic::mk_vGravity = Vector3(0.0f, -9.8f, 0.0f);

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
	m_CollisionType = new CollisionType();
	float direction = 1.0f;

	for (i = 0; i < m_RigidBodyList.size(); ++i)
	{
		//m_RigidBodyList[i]->DoPhysicJump(Physic::mk_fDeltaTime);
		m_RigidBodyList[i]->DoPhysicMove(Physic::mk_fDeltaTime, direction);
		direction *= -1;
	}


	for (i = 0; i < m_RigidBodyList.size(); ++i)
	{
		//second loop not check a rigidbody with itself and previous rigidbody (double check)
		for (j = i + 1; j < m_RigidBodyList.size(); ++j)
		{
			//if collision was between SPHERE-SPHERE
			if ((m_RigidBodyList[i]->GetColliderType() == 0) && (m_RigidBodyList[j]->GetColliderType() == 0))
			{
				if (m_CollisionType->CollisionDetectionSphereSphere(m_RigidBodyList[i]->GetCollider(), m_RigidBodyList[j]->GetCollider()))
				{
					m_CollisionType->ResolveCollisionSphereSphere(
						*m_RigidBodyList[i],
						*m_RigidBodyList[j],
						m_RigidBodyList[i]->GetCollider(),
						m_RigidBodyList[j]->GetCollider()
						);
				}
			}
			//if collision was between BOX-BOX
			else if ((m_RigidBodyList[i]->GetColliderType() == 1) && (m_RigidBodyList[j]->GetColliderType() == 1))
			{
				if (m_CollisionType->CollisionDetectionBoxBox(m_RigidBodyList[i]->GetCollider(), m_RigidBodyList[j]->GetCollider()))
				{
					m_CollisionType->ResolveCollisionBoxBox(
						*m_RigidBodyList[i],
						*m_RigidBodyList[j],
						m_RigidBodyList[i]->GetCollider(),
						m_RigidBodyList[j]->GetCollider()
						);
				}
			}
			//if collision was between BOX-SPHERE or SPHERE-BOX
			else if ((m_RigidBodyList[i]->GetColliderType() == 1) && (m_RigidBodyList[j]->GetColliderType() == 0)
				|| (m_RigidBodyList[i]->GetColliderType() == 0) && (m_RigidBodyList[j]->GetColliderType() == 1))
			{
				if (m_CollisionType->CollisionDetectionBoxSphere(m_RigidBodyList[i]->GetCollider(), m_RigidBodyList[j]->GetCollider())
					|| m_CollisionType->CollisionDetectionBoxSphere(m_RigidBodyList[j]->GetCollider(), m_RigidBodyList[i]->GetCollider()))
				{
					m_CollisionType->ResolveCollisionBoxSphere(
						*m_RigidBodyList[i],
						*m_RigidBodyList[j],
						m_RigidBodyList[i]->GetCollider(),
						m_RigidBodyList[j]->GetCollider()
						);
				}
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
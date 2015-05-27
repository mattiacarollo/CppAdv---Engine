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
			//if collision was between SPHERE-SPHERE
			if ((m_RigidBodyList[i]->GetColliderType() == 0) && (m_RigidBodyList[j]->GetColliderType() == 0))
			{
				if (CollisionDetectionSphereSphere(m_RigidBodyList[i]->GetCollider(), m_RigidBodyList[j]->GetCollider()))
				{
					ResolveCollisionSphereSphere(
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
				if (CollisionDetectionBoxBox(m_RigidBodyList[i]->GetCollider(), m_RigidBodyList[j]->GetCollider()))
				{
					ResolveCollisionBoxBox(
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
				if (CollisionDetectionBoxSphere(m_RigidBodyList[i]->GetCollider(), m_RigidBodyList[j]->GetCollider())
					|| CollisionDetectionBoxSphere(m_RigidBodyList[j]->GetCollider(), m_RigidBodyList[i]->GetCollider()))
				{
					ResolveCollisionBoxSphere(
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

//SPHERE-SPHERE
bool Physic::CollisionDetectionSphereSphere(Collider* colliderRb0, Collider* colliderRb1)
{
	// Calculate squared distance between centers
	Vector3 centersDistance = colliderRb0->GetWorldPosition() - colliderRb1->GetWorldPosition();
	float distance = VectorOp::DotProduct(centersDistance, centersDistance);

	// Spheres intersect if squared distance is less than squared sum of radii
	float radiusSum = ((SphereCollider*)colliderRb0)->GetRadius() + ((SphereCollider*)colliderRb1)->GetRadius();
	
	if (distance < (radiusSum * radiusSum))
	{
		m_fCompenetration = radiusSum - sqrtf(distance);
		return true;
	}

	return false;
}


void Physic::ResolveCollisionSphereSphere(RigidBody& rigidbody0, RigidBody& rigidbody1, Collider* colliderRb0, Collider* colliderRb1)
{
	Vector3 force = rigidbody0.GetVelocity() + rigidbody1.GetVelocity();

	Vector3 centersDistance = colliderRb0->GetWorldPosition() - colliderRb1->GetWorldPosition();
	centersDistance.Normalize();
	Vector3 poa = centersDistance * ((SphereCollider*)colliderRb0)->GetRadius();

	m_Collision = new Collision(&rigidbody0, &rigidbody1, m_fCompenetration, poa, force, centersDistance);
	m_Collision->ApplyCollision();
}

//BOX-BOX
bool Physic::CollisionDetectionBoxBox(Collider* colliderRb0, Collider* colliderRb1)
{	
	//Compute Collision on first axis system so first can be seen as an AABB
	Vector3 centersDistance(colliderRb1->GetWorldPosition());
	Vector3 SecondBoxCenterInFirstBoxSystem(centersDistance);
	centersDistance -= colliderRb0->GetWorldPosition();
	centersDistance *= -1.0f;
	MatrixOp::Rotate<MatrixOp::ToObjSpace>(((BoxCollider*)colliderRb0)->GetRotation().ToMatrix(), SecondBoxCenterInFirstBoxSystem, SecondBoxCenterInFirstBoxSystem);
	Vector3 radiiSum(((BoxCollider*)colliderRb0)->GetHalfSize());
	radiiSum += ((BoxCollider*)colliderRb1)->GetHalfSize();

	//SphereTest for early fast reject
	bool SphereConsideration = (centersDistance.getX()*centersDistance.getX()) < (radiiSum.getX()*radiiSum.getX()) &&
		(centersDistance.getY()*centersDistance.getY()) < (radiiSum.getY()*radiiSum.getY()) &&
		(centersDistance.getZ()*centersDistance.getZ()) < (radiiSum.getZ()*radiiSum.getZ()) && (centersDistance.SqrMagnitude()) < (radiiSum.SqrMagnitude());

	if (SphereConsideration)
	{
		return false;
	}

	//Compute Min and Max for first box
	Vector3 Min(colliderRb0->GetWorldPosition() - ((BoxCollider*)colliderRb0)->GetHalfSize());
	Vector3 Max(colliderRb0->GetWorldPosition() + ((BoxCollider*)colliderRb0)->GetHalfSize());
	MatrixOp::Rotate<MatrixOp::ToObjSpace>(((BoxCollider*)colliderRb0)->GetRotation().ToMatrix(), Min, Min);
	MatrixOp::Rotate<MatrixOp::ToObjSpace>(((BoxCollider*)colliderRb0)->GetRotation().ToMatrix(), Max, Max);
	Vector3 SecondHalfSizeInFistSystem(((BoxCollider*)colliderRb1)->GetHalfSize());
	MatrixOp::Rotate<MatrixOp::ToObjSpace>(((BoxCollider*)colliderRb1)->GetRotation().ToMatrix(), SecondHalfSizeInFistSystem, SecondHalfSizeInFistSystem);
	MatrixOp::Rotate<MatrixOp::ToObjSpace>(((BoxCollider*)colliderRb0)->GetRotation().ToMatrix(), SecondHalfSizeInFistSystem, SecondHalfSizeInFistSystem);

	//Optimization TO DO
	//0 1 3 7 6 4 5 2
	if (bo(colliderRb0, SecondBoxCenterInFirstBoxSystem, SecondHalfSizeInFistSystem, Min, Max))			//Second vs first
	{
		m_vBoxCentersDistance = centersDistance;
		return true;
	}
	else if (bo(colliderRb1, SecondBoxCenterInFirstBoxSystem, SecondHalfSizeInFistSystem, Min, Max))	//first vs Second
	{
		return true;
	}

	return false;
}

void Physic::ResolveCollisionBoxBox(RigidBody& rigidbody0, RigidBody& rigidbody1, Collider* colliderRb0, Collider* colliderRb1)
{
	Vector3 force = rigidbody0.GetVelocity() + rigidbody1.GetVelocity();

	m_fCompenetration = m_aBoxCompenetration[0];
	m_vBoxVertex[m_aBoxIndexes[0]][0] *= m_aBoxCompenetration[0];
	m_vBoxVertex[m_aBoxIndexes[0]][1] *= m_aBoxCompenetration[0];
	m_vBoxVertex[m_aBoxIndexes[0]][2] *= m_aBoxCompenetration[0];
	//centroid of points which is the point of collision impact
	for (unsigned int i = 1; i < m_iPointsInside; ++i)
	{
		m_vBoxVertex[m_aBoxIndexes[0]][0] += m_vBoxVertex[m_aBoxIndexes[i]][0];
		m_vBoxVertex[m_aBoxIndexes[0]][1] += m_vBoxVertex[m_aBoxIndexes[i]][1];
		m_vBoxVertex[m_aBoxIndexes[0]][2] += m_vBoxVertex[m_aBoxIndexes[i]][2];
		m_fCompenetration += m_aBoxCompenetration[i];
		m_aBoxCompenetration[0] = std::fmaxf(m_aBoxCompenetration[0], m_aBoxCompenetration[i]);
	}
	m_vBoxVertex[m_aBoxIndexes[0]][0] /= m_fCompenetration;
	m_vBoxVertex[m_aBoxIndexes[0]][1] /= m_fCompenetration;
	m_vBoxVertex[m_aBoxIndexes[0]][2] /= m_fCompenetration;

	//Compute normal by clamping on max value
	m_vBoxCentersDistance.Normalize();
	float x, y, z;
	x = m_vBoxCentersDistance.getX();
	y = m_vBoxCentersDistance.getY();
	z = m_vBoxCentersDistance.getZ();
	if (x > y)
	{
		if (x > z)
		{
			m_vBoxCentersDistance.Set(x, 0, 0);
		}
		else
		{
			m_vBoxCentersDistance.Set(0, 0, z);
		}
	}
	else
	{
		if (y > z)
		{
			m_vBoxCentersDistance.Set(0, y, 0);
		}
		else
		{
			m_vBoxCentersDistance.Set(0, 0, z);
		}
	}
	m_vBoxCentersDistance.Normalize();


	m_Collision = new Collision(&rigidbody0, &rigidbody1, m_aBoxCompenetration[0], m_vBoxVertex[m_aBoxIndexes[0]], force, m_vBoxCentersDistance);
	m_Collision->ApplyCollision();
}

//BOX-SPHERE
bool Physic::CollisionDetectionBoxSphere(Collider* colliderRb0, Collider* colliderRb1)
{
	Vector3 SphereCenterInBoxSystem(colliderRb1->GetWorldPosition());
	MatrixOp::Rotate<MatrixOp::ToObjSpace>(((BoxCollider*)colliderRb0)->GetRotation().ToMatrix(), SphereCenterInBoxSystem, SphereCenterInBoxSystem);
	Vector3 Min(colliderRb0->GetWorldPosition() - ((BoxCollider*)colliderRb0)->GetHalfSize());
	Vector3 Max(colliderRb0->GetWorldPosition() + ((BoxCollider*)colliderRb0)->GetHalfSize());
	MatrixOp::Rotate<MatrixOp::ToObjSpace>(((BoxCollider*)colliderRb0)->GetRotation().ToMatrix(), Min, Min);
	MatrixOp::Rotate<MatrixOp::ToObjSpace>(((BoxCollider*)colliderRb0)->GetRotation().ToMatrix(), Max, Max);

	float distance = 0;
	if (SphereCenterInBoxSystem.getX() < Min.getX())
	{
		distance += (SphereCenterInBoxSystem.getX() - Min.getX()) *(SphereCenterInBoxSystem.getX() - Min.getX());
	}
	else
	{
		if (SphereCenterInBoxSystem.getX() > Max.getX())
		{
			distance += (SphereCenterInBoxSystem.getX() - Max.getX()) *(SphereCenterInBoxSystem.getX() - Max.getX());
		}
	}
	if (SphereCenterInBoxSystem.getY() < Min.getY())
	{
		distance += (SphereCenterInBoxSystem.getY() - Min.getY()) *(SphereCenterInBoxSystem.getY() - Min.getY());
	}
	else
	{
		if (SphereCenterInBoxSystem.getY() > Max.getY())
		{
			distance += (SphereCenterInBoxSystem.getY() - Max.getY()) *(SphereCenterInBoxSystem.getY() - Max.getY());
		}
	}
	if (SphereCenterInBoxSystem.getZ() < Min.getZ())
	{
		distance += (SphereCenterInBoxSystem.getZ() - Min.getZ()) *(SphereCenterInBoxSystem.getZ() - Min.getZ());
	}
	else
	{
		if (SphereCenterInBoxSystem.getZ() > Max.getZ())
		{
			distance += (SphereCenterInBoxSystem.getZ() - Max.getZ()) *(SphereCenterInBoxSystem.getZ() - Max.getZ());
		}
	}
	if (distance < ((SphereCollider*)colliderRb1)->GetRadius() * ((SphereCollider*)colliderRb1)->GetRadius()){
		m_fCompenetration = ((SphereCollider*)colliderRb1)->GetRadius() - sqrtf(distance);
		return true;
	}

	return false;
}

void Physic::ResolveCollisionBoxSphere(RigidBody& rigidbody0, RigidBody& rigidbody1, Collider* colliderRb0, Collider* colliderRb1)
{
	Vector3 force = rigidbody0.GetVelocity() + rigidbody1.GetVelocity();

	Vector3 centersDistance = colliderRb0->GetWorldPosition() - colliderRb1->GetWorldPosition();
	centersDistance.Normalize();
	Vector3 poa = centersDistance * ((SphereCollider*)colliderRb1)->GetRadius();

	m_Collision = new Collision(&rigidbody0, &rigidbody1, m_fCompenetration, poa, force, centersDistance);
	m_Collision->ApplyCollision();
}

bool Physic::bo(Collider* colliderRb, Vector3 SecondBoxCenterInFirstBoxSystem, Vector3 SecondHalfSizeInFistSystem, Vector3 Min, Vector3 Max)
{
	
	m_vBoxVertex[0] = (SecondBoxCenterInFirstBoxSystem);
	m_vBoxVertex[0][0] += SecondHalfSizeInFistSystem[0];
	m_vBoxVertex[0][1] += SecondHalfSizeInFistSystem[1];
	m_vBoxVertex[0][2] += SecondHalfSizeInFistSystem[2];

	m_vBoxVertex[1] = (SecondBoxCenterInFirstBoxSystem);
	m_vBoxVertex[1][0] += SecondHalfSizeInFistSystem[0];
	m_vBoxVertex[1][1] += SecondHalfSizeInFistSystem[1];
	m_vBoxVertex[1][2] -= SecondHalfSizeInFistSystem[2];

	m_vBoxVertex[2] = (SecondBoxCenterInFirstBoxSystem);
	m_vBoxVertex[2][0] += SecondHalfSizeInFistSystem[0];
	m_vBoxVertex[2][1] -= SecondHalfSizeInFistSystem[1];
	m_vBoxVertex[2][2] += SecondHalfSizeInFistSystem[2];

	m_vBoxVertex[3] = (SecondBoxCenterInFirstBoxSystem);
	m_vBoxVertex[3][0] += SecondHalfSizeInFistSystem[0];
	m_vBoxVertex[3][1] -= SecondHalfSizeInFistSystem[1];
	m_vBoxVertex[3][2] -= SecondHalfSizeInFistSystem[2];

	m_vBoxVertex[4] = (SecondBoxCenterInFirstBoxSystem);
	m_vBoxVertex[4][0] -= SecondHalfSizeInFistSystem[0];
	m_vBoxVertex[4][1] += SecondHalfSizeInFistSystem[1];
	m_vBoxVertex[4][2] += SecondHalfSizeInFistSystem[2];

	m_vBoxVertex[5] = (SecondBoxCenterInFirstBoxSystem);
	m_vBoxVertex[5][0] -= SecondHalfSizeInFistSystem[0];
	m_vBoxVertex[5][1] += SecondHalfSizeInFistSystem[1];
	m_vBoxVertex[5][2] -= SecondHalfSizeInFistSystem[2];

	m_vBoxVertex[6] = (SecondBoxCenterInFirstBoxSystem);
	m_vBoxVertex[6][0] -= SecondHalfSizeInFistSystem[0];
	m_vBoxVertex[6][1] -= SecondHalfSizeInFistSystem[1];
	m_vBoxVertex[6][2] += SecondHalfSizeInFistSystem[2];

	m_vBoxVertex[7] = (SecondBoxCenterInFirstBoxSystem);
	m_vBoxVertex[7][0] -= SecondHalfSizeInFistSystem[0];
	m_vBoxVertex[7][1] -= SecondHalfSizeInFistSystem[1];
	m_vBoxVertex[7][2] -= SecondHalfSizeInFistSystem[2];

	//Compute points inside
	m_iPointsInside = 0;
	bool isInside = false;
	for (unsigned int i = 0; i < 8; ++i)
	{
		isInside = m_vBoxVertex[i][0] > Min[0] && m_vBoxVertex[i][1] > Min[1] && m_vBoxVertex[i][2] > Min[2] &&
			m_vBoxVertex[i][0] < Max[0] && m_vBoxVertex[i][1] < Max[1] && m_vBoxVertex[i][2] < Max[2];
		if (isInside)
		{
			m_aBoxIndexes[m_iPointsInside] = i;
			m_aBoxCompenetration[m_iPointsInside] = (m_vBoxVertex[i] - colliderRb->GetWorldPosition()).SqrMagnitude();
			++m_iPointsInside;
		}
	}

	if (m_iPointsInside)
	{
		return true;
	}

	return false;
}
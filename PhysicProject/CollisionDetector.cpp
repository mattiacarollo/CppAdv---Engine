#include "CollisionDetector.h"

CollisionDetector::CollisionDetector()
{
	m_Collision = new Collision();
}

CollisionDetector::~CollisionDetector()
{
}

//SPHERE-PLANE
bool CollisionDetector::CollisionDetectionSpherePlane(RigidBody& rigidbody0)
{
	// troviamo il punto di contatto della sfera verso il piano
	Vector3 temp = { 0.f, -1.f, 0.f };
	m_Collision->SetInpactPoint(temp);
	m_Collision->SetInpactPoint( 
		m_Collision->GetInpactPoint() * rigidbody0.GetRadius() 
		);

	VectorOp::VectorialProduct(rigidbody0.GetAngularVelocity(), m_Collision->GetInpactPoint(), temp);
	m_Collision->SetInpactVelocity(temp);

	m_Collision->SetInpactPoint(
		rigidbody0.GetPosition() + m_Collision->GetInpactPoint()
		);
	m_Collision->SetInpactVelocity(
		rigidbody0.GetVelocity() + m_Collision->GetInpactVelocity()
		);

	//c[0].deformation = -(A * c[0].inpactPoint[0] + B * c[0].inpactPoint[1] + C * c[0].inpactPoint[2] + D);
	m_Collision->SetDeformation(
		-(/*0.0f * m_Collision->GetInpactPoint()*/ + 5.0f)
		);
	
	if (m_Collision->GetDeformation() < 0)
	{
		return false;
	}

	temp = { 0.f, -1.f, 0.f };
	m_Collision->SetNormalVector(temp);

	m_Collision->SetInpactVelocity(m_Collision->GetInpactVelocity() * -1.0f);

	return true;
}

void CollisionDetector::ResolveCollisionSpherePlane(RigidBody& rigidbody0, float k, float l, float m)
{
	m_Collision->ApplyCollision(&rigidbody0, NULL, k, l, m);
}

//CUBE-PLANE
bool CollisionDetector::CollisionDetectionCubePlane(RigidBody& rigidbody0)
{
	return false;
}

void CollisionDetector::ResolveCollisionCubePlane(RigidBody& rigidbody0, float k, float l, float m)
{
	m_Collision->ApplyCollision(&rigidbody0, NULL, k, l, m);
}




//SPHERE-SPHERE
bool CollisionDetector::CollisionDetectionSphereSphere(RigidBody& rigidbody0, RigidBody& rigidbody1)
{
	return false;
}

void CollisionDetector::ResolveCollisionSphereSphere(RigidBody& rigidbody0, RigidBody& rigidbody1, float k, float l, float m)
{
	
}

//BOX-BOX
bool CollisionDetector::CollisionDetectionBoxBox(RigidBody& rigidbody0, RigidBody& rigidbody1)
{
	return false;
}

void CollisionDetector::ResolveCollisionBoxBox(RigidBody& rigidbody0, RigidBody& rigidbody1, float k, float l, float m)
{

}

//BOX-SPHERE
bool CollisionDetector::CollisionDetectionBoxSphere(RigidBody& rigidbody0, RigidBody& rigidbody1)
{
	return false;
}

void CollisionDetector::ResolveCollisionBoxSphere(RigidBody& rigidbody0, RigidBody& rigidbody1, float k, float l, float m)
{
	
}
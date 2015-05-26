#include <iostream>
#include "Collision.h"
#include "RigidBody.h"
#include "Physic.h"


Collision::Collision(){
}

Collision::~Collision()
{
}

Collision::Collision(RigidBody* rigidbodyfirst, RigidBody* rigidbodysecond, const Vector3& pointOfApplication, const Vector3& force, const Vector3& normal)
	: m_firstObj(rigidbodyfirst), 
	  m_secondObj(rigidbodysecond), 
	  m_vpointOfApplication(pointOfApplication), 
	  m_vforce(force), 
	  m_vnormal(normal)
{
}

void Collision::ApplyCollision()
{
	float f;
	float vn;
	float modVtang;
	vn = VectorOp::DotProduct(m_vforce, m_vnormal);
	Vector3 Vnorm = m_vnormal*vn;
	Vector3 Vtang = m_vforce - Vnorm;
	// K = coefficente elastico L = coefficente anaelastico  TO DO
	//f = (0.5f * _deformation) + (5.0f * vn);
	f = (0.5f * 1.0f) + (5.0f * vn);
	m_vnormal *= f;
	// forza reagente (modulo) -> m = coefficente attrito TO DO
	f *= 5;
	modVtang = Vtang.Modulus();
	if (f<0)
		f = 0;
	Vtang *= f;
	if (modVtang > 9.8f * Physic::mk_fDeltaTime)
		Vtang.Normalize();
	else
		Vtang /= (9.8f * Physic::mk_fDeltaTime);

	m_vnormal += Vtang;

	m_firstObj->ApplyForce(m_vnormal, m_vpointOfApplication);
	m_secondObj->ApplyForce(m_vnormal*-1.0f, m_vpointOfApplication);
};
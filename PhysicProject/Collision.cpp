#include <iostream>
#include "Collision.h"
#include "RigidBody.h"
#include "Physic.h"


Collision::Collision(float deformation, const Vector3& pointOfApplication, const Vector3& normal)
: m_fdeformation(deformation), m_vpointOfApplication(pointOfApplication), m_vnormal(normal)
{
}

void Collision::ApplyCollision()
{
	//TO DO
	float f;
	float vn;
	float modVtang;
	vn = VectorOp::DotProduct(m_vforce, m_vnormal);
	Vector3 Vnorm = m_vnormal*vn;
	Vector3 Vtang = m_vforce - Vnorm;
	// K = coefficente elastico L = coefficente anaelastico  TO DO
	f = (0.5f * m_fdeformation) + (5.0f * vn); 
	m_vnormal *= f;
	// forza reagente (modulo) -> m = coefficente attrito TO DO
	f *= 5;	
	modVtang = Vtang.Modulus();
	if (f<0)
		f = 0;
	Vtang*=f;
	if (modVtang > 9.8f * Physic::mk_fDeltaTime)
		Vtang.Normalize();
	else
		Vtang /= (9.8f * Physic::mk_fDeltaTime);
	
	m_vnormal += Vtang;

	m_firstObj->ApplyForce(m_vnormal, m_vpointOfApplication);
	m_secondObj->ApplyForce(m_vnormal*-1.0f, m_vpointOfApplication);

	std::cout << "After Collision Handling" << std::endl;
	std::cout << "Collision Force: " << "( " << m_vnormal.getX() << ", " << m_vnormal.getY() << ", " << m_vnormal.getZ() << ") " << std::endl;
	//m_firstObj->PrintStatus();
	//m_secondObj->PrintStatus();

};

void Collision::SetBodies(RigidBody*first,RigidBody*second)
{
	m_firstObj = first;
	m_secondObj = second;
	m_vforce += first->GetVelocity();
	m_vforce += second->GetVelocity();
}
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
};
#pragma once

#include "Vector3.h"

class RigidBody;
class Collision
{

public:
	Collision(float deformation, const Vector3& pointOfApplication, const Vector3& normal);
	void SetBodies(RigidBody* first,RigidBody* second);
	void ApplyCollision();

private:
	RigidBody* m_firstObj;
	RigidBody* m_secondObj;
	float m_fdeformation;
	Vector3 m_vpointOfApplication;
	Vector3 m_vforce;
	Vector3 m_vnormal;
};
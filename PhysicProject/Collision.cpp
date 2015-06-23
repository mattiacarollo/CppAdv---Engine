#include "Collision.h"

Collision::Collision(){
}

Collision::~Collision()
{
}

Collision::Collision(RigidBody* rigidbodyfirst, RigidBody* rigidbodysecond, float deformation, const Vector3& pointOfApplication, const Vector3& force, const Vector3& normal)
	: m_firstObj(rigidbodyfirst),
	  m_secondObj(rigidbodysecond),
	  m_fDeformation(deformation),
	  m_vpointOfApplication(pointOfApplication),
	  m_vforce(force),
	  m_vnormal(normal)
{
}

void Collision::ApplyCollision()
{
	float force, modVtang;
	float vn = VectorOp::DotProduct(m_vforce, m_vnormal);;
	Vector3 Vnorm = m_vnormal*vn;
	Vector3 Vtang = m_vforce - Vnorm;

	// K = coefficente elastico L = coefficente anaelastico  TO DO
	force = (0.5f * m_fDeformation) + (5.0f * vn);
	m_vnormal *= force;

	force *= 5;								// forza reagente (modulo) -> m = coefficente attrito TO DO
	modVtang = Vtang.Modulus();

	if (force < 0)
	{
		force = 0;
	}

	Vtang *= force;
	if (modVtang > 9.8f * Physic::mk_fDeltaTime)
	{
		Vtang.Normalize();
	}
	else
	{
		Vtang /= (9.8f * Physic::mk_fDeltaTime);
	}

	m_vnormal += Vtang;

	m_firstObj->ApplyForce(m_vnormal, m_vpointOfApplication);
	m_secondObj->ApplyForce(m_vnormal*-1.0f, m_vpointOfApplication);

	///-----------------MARABESE
	//float f;
	//float vn;
	//float modVtang;
	//Vector3 Vtang, Ftang, Fnorm;

	//vn = VectorOp::DotProduct(m_vforce, m_vnormal);
	//Vtang = m_vnormal;
	//Vtang *= vn;
	//Vtang -= m_vforce;

	//f = (600.f * m_fDeformation) + (100.f * vn); //600.f=K , 100.f=L
	//if (f < 0) f = 0;
	//Fnorm = m_vnormal;
	//Fnorm *= f;

	//f *= 5; //5=m		// forza attrito (modulo)
	//modVtang = Vtang.Modulus();
	//Ftang = Vtang;
	//Ftang *= f;

	//if (modVtang > 9.8f * 0.025f)	//0.025 --> DT
	//{
	//	Ftang /= modVtang;
	//}
	//else
	//{
	//	Ftang /= (9.8f * 0.025f);//0.025 --> DT
	//}

	//Fnorm += Ftang;	// ora Fnorm e' la F totale

	//if (m_firstObj != NULL) 
	//	m_firstObj->ApplyForce(Fnorm, m_vpointOfApplication);
	//Fnorm[0] = -Fnorm[0];
	//Fnorm[1] = -Fnorm[1];
	//Fnorm[2] = -Fnorm[2];
	//if (m_secondObj != NULL)
	//	m_secondObj->ApplyForce(Fnorm, m_vpointOfApplication);





	/*float m1, m2, x1, x2;
	Vector3 v1, v2, v1x, v2x, v1y, v2y;

	v1 = m_firstObj->GetVelocity();
	x1 = VectorOp::DotProduct(m_vnormal, v1);
	v1x = m_vnormal * x1;
	v1y = v1 - v1x;
	m1 = m_firstObj->GetMass();

	m_vnormal = m_vnormal * -1.0f;
	v2 = m_secondObj->GetVelocity();
	x2 = VectorOp::DotProduct(m_vnormal, v2);
	v2x = m_vnormal * x2;
	v2y = v2 - v2x;
	m2 = m_secondObj->GetMass();

	Vector3 firstRbVel = { v1x*(m1 - m2) / (m1 + m2) + v2x*(2 * m2) / (m1 + m2) + v1y };
	Vector3 secondRbVel = { v1x*(2 * m1) / (m1 + m2) + v2x*(m2 - m1) / (m1 + m2) + v2y };

	m_firstObj->SetVelocity(firstRbVel);
	m_secondObj->SetVelocity(secondRbVel);*/
};
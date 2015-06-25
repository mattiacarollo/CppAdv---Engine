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
	Vector3 temp = { 0.f, 1.f, 0.f };	// normale del piano (0, 1, 0)

	m_Collision->SetInpactPoint(temp * -1);
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

	m_Collision->SetDeformation(
		((m_Collision->GetInpactPoint()).getX() * 0.0f +
		(m_Collision->GetInpactPoint()).getY() * 1.0f +
		(m_Collision->GetInpactPoint()).getZ() * 0.0f + 0.0f) * -1.0f
		);
	
	// Se Deformazione = 0 allora sono sul piano
	// Se Deformazione < 0 allora sono sopra al piano
	// Se Deformazione > 0 allora lo sto compenetrando
	if (m_Collision->GetDeformation() < 0)
	{
		return false;
	}

	temp = { 0.f, 1.f, 0.f };
	m_Collision->SetNormalVector(temp);

	m_Collision->SetInpactVelocity(m_Collision->GetInpactVelocity() * -1.0f);

	return true;
}

void CollisionDetector::ResolveCollisionSpherePlane(RigidBody& rigidbody0, float k, float l, float m)
{
	m_Collision->ApplyCollision(&rigidbody0, NULL, k, l, m);
}

//CUBE-PLANE
int CollisionDetector::CollisionDetectionCubePlane(RigidBody& rigidbody0)
{
	int i;
	int n = 0;
	Vector3 temp = VectorOp::Zero;

	//8 è il numero di verici del cubo
	//ASSICURATI CHE NON SIA VERAMENTE IL MAXCOLLISIONI POSSIBILI
	int MaxCollisioni = 8;

	for (i = 0; i < MaxCollisioni; i++) {
		/*MatrixOp::Rotate<MatrixOp::ToWorldSpace>(rigidbody0.GetRotationMatrix(), rigidbody0.m_vVerteces[i], temp);
		m_aCollision.push_back(m_Collision);
		m_aCollision.at(n)->SetInpactPoint(temp);
		VectorOp::VectorialProduct(rigidbody0.GetAngularVelocity(), m_aCollision.at(n)->GetInpactPoint(), temp);
		m_aCollision.at(n)->SetInpactVelocity(temp);
		m_aCollision.at(n)->SetInpactPoint(
			rigidbody0.GetPosition() + m_aCollision.at(n)->GetInpactPoint()
			);
		m_aCollision.at(n)->SetInpactVelocity(
			rigidbody0.GetVelocity() + m_aCollision.at(n)->GetInpactVelocity()
			);

		m_aCollision.at(n)->SetDeformation(
			((m_aCollision.at(n)->GetInpactPoint()).getX() * 0.0f +
			(m_aCollision.at(n)->GetInpactPoint()).getY() * 1.0f +
			(m_aCollision.at(n)->GetInpactPoint()).getZ() * 0.0f + 0.0f) * -1.0f
			);	
		if (m_aCollision.at(n)->GetDeformation() < 0)
		{
			continue;
		}

		m_aCollision.at(n)->SetNormalVector(Vector3{0.0f, 1.0f, 0.0f});
		m_aCollision.at(n)->SetInpactVelocity( m_aCollision.at(n)->GetInpactVelocity() * -1.0f);*/
		MatrixOp::Rotate<MatrixOp::ToWorldSpace>(rigidbody0.GetRotationMatrix(), rigidbody0.m_vVerteces[i], temp);
		m_aCollision.push_back(m_Collision);
		m_aCollision.at(0)->SetInpactPoint(temp);
		VectorOp::VectorialProduct(rigidbody0.GetAngularVelocity(), m_aCollision.at(0)->GetInpactPoint(), temp);
		m_aCollision.at(0)->SetInpactVelocity(temp);
		m_aCollision.at(0)->SetInpactPoint(
			rigidbody0.GetPosition() + m_aCollision.at(0)->GetInpactPoint()
			);
		m_aCollision.at(0)->SetInpactVelocity(
			rigidbody0.GetVelocity() + m_aCollision.at(0)->GetInpactVelocity()
			);

		m_aCollision.at(0)->SetDeformation(
			((m_aCollision.at(0)->GetInpactPoint()).getX() * 0.0f +
			(m_aCollision.at(0)->GetInpactPoint()).getY() * 1.0f +
			(m_aCollision.at(0)->GetInpactPoint()).getZ() * 0.0f + 0.0f) * -1.0f
			);
		if (m_aCollision.at(0)->GetDeformation() < 0)
		{
			continue;
		}

		m_aCollision.at(0)->SetNormalVector(Vector3{ 0.0f, 1.0f, 0.0f });
		m_aCollision.at(0)->SetInpactVelocity(m_aCollision.at(0)->GetInpactVelocity() * -1.0f);

		++n;
		if (n == MaxCollisioni)
		{
			break;
		}
	}

	return n;
}

void CollisionDetector::ResolveCollisionCubePlane(RigidBody& rigidbody0, float k, float l, float m, int nCollisions)
{
	for (int i = 0; i < nCollisions; ++i)
	{
		m_aCollision.at(i)->ApplyCollision(&rigidbody0, NULL, k, l, m);
	}
}




//SPHERE-SPHERE
bool CollisionDetector::CollisionDetectionSphereSphere(RigidBody& rigidbody0, RigidBody& rigidbody1)
{
	float d;
	const float r1 = rigidbody0.GetRadius();
	Vector3 temp = VectorOp::Zero;

	m_Collision->SetInpactPoint(
		rigidbody1.GetPosition() - rigidbody0.GetPosition()
		);
	MatrixOp::Rotate<MatrixOp::ToObjSpace>(rigidbody0.GetRotationMatrix(), m_Collision->GetInpactPoint(), temp);
	m_Collision->SetInpactPoint(temp);

	temp = {
		m_Collision->GetInpactPoint().getX(),
		m_Collision->GetInpactPoint().getY(),
		m_Collision->GetInpactPoint().getZ()
	};

	if (m_Collision->GetInpactPoint().getX() > r1)
	{
		temp.SetX(r1);
	}
	if (m_Collision->GetInpactPoint().getX() < -r1)
	{
		temp.SetX(-r1);
	}
	if (m_Collision->GetInpactPoint().getY() > r1)
	{
		temp.SetY(r1);
	}
	if (m_Collision->GetInpactPoint().getY() < -r1)
	{
		temp.SetY(-r1);
	}
	if (m_Collision->GetInpactPoint().getZ() > r1)
	{
		temp.SetZ(r1);
	}
	if (m_Collision->GetInpactPoint().getZ() < -r1)
	{
		temp.SetZ(-r1);
	}
	m_Collision->SetInpactPoint(temp);

	// trovato il punto relativo d'impatto, rendiamolo assoluto
	MatrixOp::Rotate<MatrixOp::ToWorldSpace>(rigidbody0.GetRotationMatrix(), m_Collision->GetInpactPoint(), temp);
	m_Collision->SetInpactPoint(temp);
	m_Collision->SetInpactPoint(
		m_Collision->GetInpactPoint() + rigidbody0.GetPosition()
		);

	// direzione e distanza (dalla Sfera verso il paral)
	m_Collision->SetNormalVector(
		m_Collision->GetInpactPoint() - rigidbody1.GetPosition()
		);
	d = m_Collision->GetNormalVector().Modulus();
	if (d > rigidbody1.GetRadius())
	{
		return false;
	}

	m_Collision->SetDeformation(rigidbody1.GetRadius() - d);
	m_Collision->SetNormalVector(m_Collision->GetNormalVector() / d);

	// la vel di impatto e' la diff tra la vel della sfera e quella del parall
	m_Collision->SetInpactVelocity(
		m_Collision->GetInpactPoint() - rigidbody1.GetPosition()
		);
	VectorOp::VectorialProduct(rigidbody1.GetAngularVelocity(), m_Collision->GetInpactVelocity(), temp);
	m_Collision->SetInpactVelocity(temp);
	m_Collision->SetInpactVelocity(
		rigidbody1.GetVelocity() + m_Collision->GetInpactVelocity()
		);

	temp = m_Collision->GetInpactPoint() - rigidbody0.GetPosition();
	VectorOp::VectorialProduct(rigidbody0.GetAngularVelocity(), temp, temp);
	temp += rigidbody0.GetVelocity();

	m_Collision->SetInpactVelocity(
		m_Collision->GetInpactVelocity() - temp
		);

	return true;
}

void CollisionDetector::ResolveCollisionSphereSphere(RigidBody& rigidbody0, RigidBody& rigidbody1, float k, float l, float m)
{
	m_Collision->ApplyCollision(&rigidbody0, &rigidbody1, k, l, m);
}

//BOX-BOX
bool CollisionDetector::CollisionDetectionBoxBox(RigidBody& rigidbody0, RigidBody& rigidbody1)
{
	return false;
}

void CollisionDetector::ResolveCollisionBoxBox(RigidBody& rigidbody0, RigidBody& rigidbody1, float k, float l, float m)
{
	m_Collision->ApplyCollision(&rigidbody0, &rigidbody1, k, l, m);
}

//BOX-SPHERE
bool CollisionDetector::CollisionDetectionBoxSphere(RigidBody& rigidbody0, RigidBody& rigidbody1)
{
	return false;
}

void CollisionDetector::ResolveCollisionBoxSphere(RigidBody& rigidbody0, RigidBody& rigidbody1, float k, float l, float m)
{
	m_Collision->ApplyCollision(&rigidbody0, &rigidbody1, k, l, m);
}
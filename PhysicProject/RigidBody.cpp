#include "RigidBody.h"

RigidBody::RigidBody(const Vector3& pos, int id, float mass,const Vector3& inertia) 
	: m_vPosition(pos), m_iID(id), m_fMass(mass)
{
	m_vVelocity=VectorOp::Zero;
	m_vInertia = inertia;
	m_vAngularVelocity = VectorOp::Zero;
	m_vQuantityOfMotion = VectorOp::Zero;
	m_vAngularMomentum = VectorOp::Zero;
	m_vForceSum = VectorOp::Zero;
	m_vMomentumSum = VectorOp::Zero;
	//m_mRotationMatrix = m_qRotation.ToMatrix();
}

RigidBody::RigidBody(const RigidBody& other)
{
	m_vPosition = other.GetPosition();
}

RigidBody::~RigidBody()
{
}

void RigidBody::DoPhysic(float DeltaTime)
{
	Vector3 tmp(m_vForceSum * DeltaTime);
	
	m_vQuantityOfMotion += tmp;

	tmp = m_vMomentumSum * DeltaTime;
	m_vAngularMomentum += tmp;
	m_vVelocity = m_vQuantityOfMotion / m_fMass;

	tmp = m_vVelocity * DeltaTime;
	m_vPosition += tmp;
	
	//MatrixOp::Rotate<MatrixOp::ToObjSpace>(m_mRotationMatrix, m_vAngularMomentum, m_vAngularVelocity);

	m_vAngularVelocity.SetX(m_vAngularVelocity.getX() / m_vInertia.getX());
	m_vAngularVelocity.SetY(m_vAngularVelocity.getY() / m_vInertia.getY());
	m_vAngularVelocity.SetZ(m_vAngularVelocity.getZ() / m_vInertia.getZ());

	Quaternion Rot(1, m_vAngularVelocity.getX()*DeltaTime / 2, m_vAngularVelocity.getY()*DeltaTime / 2, m_vAngularVelocity.getZ()*DeltaTime / 2);

	Rot.Normalize();
	m_qRotation = m_qRotation*Rot;
	m_qRotation.Normalize();
	//MatrixOp::Rotate<MatrixOp::ToWorldSpace>(m_mRotationMatrix, m_vAngularVelocity, m_vAngularVelocity);
	
	//m_mRotationMatrix = m_qRotation.ToMatrix();

	//m_vForceSum += Physic::mk_vGravity*m_fMass;
	m_vForceSum += Physic::mk_vGravity/m_fMass;
}

//void RigidBody::DoPhysic(float DeltaTime)
//{
//	Vector3 m_vF;
//	Vector3 m_vA;
//
//	Matrix::MoltiplicaVettoreScalare(Physic::mk_vGravity, m_fMass, m_vF);
//
//	//movimento laterale sul terreno
//	if (m_vPosition[1] + 5 < 1) {
//		float d = 1 - (m_vPosition[1] + 5);
//		d *= 4000;
//		d -= m_vVelocity[1] * 100;
//		if (d > 0) m_vF[1] += d;
//	}
//
//	if (5 - m_vPosition[0] < 1) {
//		float d = 1 - (5 - m_vPosition[0]);
//		d *= 4000;
//		d -= m_vVelocity[1] * 50;
//		if (d > 0) m_vF[0] -= d;
//	}
//
//	if (m_vPosition[0] + 5 < 1)
//	{
//		float d = 1 - (m_vPosition[0] + 5);
//		d *= 4000;
//		d += m_vVelocity[1] * 50;
//		if (d > 0) m_vF[0] += d;
//	}
//
//	//movimento di caduta
//	Matrix::DividiVettoreScalare(m_vF, m_fMass, m_vA);
//	Matrix::MoltiplicaVettoreScalare(m_vA, DeltaTime, m_vA);
//	Matrix::SommaVettori(m_vVelocity, m_vA, m_vVelocity);
//	Matrix::MoltiplicaVettoreScalare(m_vVelocity, DeltaTime, m_vA);
//	Matrix::SommaVettori(m_vPosition, m_vA, m_vPosition);
//}

void RigidBody::ApplyForce(const Vector3& force, const Vector3& pointOfApplication)
{
	SumForceToTotalForce(force);
	Vector3 ForceOnPoint(pointOfApplication-m_vPosition);
	VectorOp::VectorialProduct(ForceOnPoint, force, ForceOnPoint);
	SumMomentumToTotalMomentum(ForceOnPoint);
}

void RigidBody::SumForceToTotalForce(const Vector3& force)
{
	m_vForceSum += force;
};

void RigidBody::SumMomentumToTotalMomentum(const Vector3& momentum)
{
	m_vMomentumSum += momentum;
};

void RigidBody::AttachCollider(Collider* Collider)
{
	m_cCollider = Collider;
}

void RigidBody::DetachCollider()
{
	delete m_cCollider;
}

int RigidBody::GetID() const
{
	return m_iID;
}

float RigidBody::GetMass() const
{
	return m_fMass;
}

//const Matrix<3, 3>& RigidBody::GetRotationMatrix() const
//{
//	return m_mRotationMatrix;
//};

const Quaternion& RigidBody::GetRotationQuaternion() const
{
	return m_qRotation;
};

const Vector3& RigidBody::GetPosition() const
{
	return m_vPosition;
}

Vector3 RigidBody::GetVelocity() const
{
	return m_vVelocity;
};

Collider* RigidBody::GetCollider() const
{
	return m_cCollider;
};

void RigidBody::SetVelocity(const Vector3& NewVelocity)
{
	m_vVelocity = NewVelocity;
};

void RigidBody::SetPosition(const Vector3& NewPosition)
{
	m_vPosition = NewPosition;
};
#include "RigidBody.h"

RigidBody::RigidBody(const Vector3& pos, int id, float mass, const Vector3& inertia)
	: m_vPosition(pos), m_iID(id), m_fMass(mass)
{
	m_vVelocity = VectorOp::Zero;
	m_vInertia = inertia;
	m_vAngularVelocity = VectorOp::Zero;
	m_vQuantityOfMotion = VectorOp::Zero;
	m_vAngularMomentum = VectorOp::Zero;
	m_vForceSum = VectorOp::Zero;
	m_vMomentumSum = VectorOp::Zero;
	m_mRotationMatrix = m_qRotation.ToMatrix();
}

RigidBody::RigidBody(const RigidBody& other)
{
	m_vPosition = other.GetPosition();
}

RigidBody::~RigidBody()
{
}

void RigidBody::UpdateMovement(float DeltaTime)
{
	Vector3 v, A;

	A = (m_vForceSum / m_fMass) * DeltaTime;

	m_vInitialVelocity += A;
	A = m_vInitialVelocity* DeltaTime;

	v = m_vForceSum * DeltaTime;
	m_vQuantityOfMotion += v;
	v = m_vMomentumSum * DeltaTime;
	m_vAngularMomentum += v;

	m_vVelocity = m_vQuantityOfMotion / m_fMass;
	v = m_vVelocity * DeltaTime;

	v += A;
	m_vPosition += v;

	MatrixOp::Rotate<MatrixOp::ToObjSpace>(m_mRotationMatrix, m_vAngularMomentum, m_vAngularVelocity);
	m_vAngularVelocity /= m_vInertia;	// v = vang
	
	Quaternion q(
		1,
		m_vAngularVelocity.getX() * DeltaTime / 2,
		m_vAngularVelocity.getY() * DeltaTime / 2,
		m_vAngularVelocity.getZ() * DeltaTime / 2
		);
	q.Normalize();
	m_qRotation *= q;
	m_qRotation.Normalize();
	
	MatrixOp::Rotate<MatrixOp::ToWorldSpace>(m_mRotationMatrix, m_vAngularVelocity, m_vAngularVelocity);
	//MatriceDaQuaternione(Rot, MRot);
}

void RigidBody::ApplyForce(const Vector3& force, const Vector3& pointOfApplication)
{
	m_vForceSum += force;
	Vector3 ForceOnPoint(pointOfApplication-m_vPosition);
	VectorOp::VectorialProduct(ForceOnPoint, force, ForceOnPoint);
	m_vMomentumSum += ForceOnPoint;
}
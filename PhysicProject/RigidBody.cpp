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

void RigidBody::DoPhysicJump(float DeltaTime)
{
	Vector3 tmp(m_vForceSum * DeltaTime);
	m_vQuantityOfMotion += tmp;						//quantity of motion (p = m*v)
	
	tmp = m_vMomentumSum * DeltaTime;
	m_vAngularMomentum += tmp;
	m_vVelocity = m_vQuantityOfMotion / m_fMass;	//velocity of center of gravity(baricentro) (v = p/m)

	tmp = m_vVelocity * DeltaTime;
	m_vPosition += tmp;
	
	//MatriceOp::Rotate<MatriceOp::ToObjSpace>(m_mRotationMatrix, m_vAngularMomentum, m_vAngularVelocity);

	m_vAngularVelocity.SetX(m_vAngularVelocity.getX() / m_vInertia.getX());
	m_vAngularVelocity.SetY(m_vAngularVelocity.getY() / m_vInertia.getY());
	m_vAngularVelocity.SetZ(m_vAngularVelocity.getZ() / m_vInertia.getZ());

	Quaternion Rot(
		1, 
		m_vAngularVelocity.getX()*DeltaTime / 2, 
		m_vAngularVelocity.getY()*DeltaTime / 2, 
		m_vAngularVelocity.getZ()*DeltaTime / 2
	);

	Rot.Normalize();
	m_qRotation = m_qRotation * Rot;
	m_qRotation.Normalize();
	//MatriceOp::Rotate<MatriceOp::ToWorldSpace>(m_mRotationMatrix, m_vAngularVelocity, m_vAngularVelocity);
	
	m_mRotationMatrix = m_qRotation.ToMatrix();

	m_vForceSum = Physic::mk_vGravity * m_fMass;

	//movimento laterale sul terreno
	//5 è il raggio
	if (m_vPosition[1] + 5 < 1) {
		float d = 1 - (m_vPosition[1] + 5);
		d *= 4000;
		d -= m_vVelocity[1] * 100;
		if (d > 0) m_vForceSum[1] += d;
	}

	/*if (5 - m_vPosition[0] < 1) {
		float d = 1 - (5 - m_vPosition[0]);
		d *= 4000;
		d -= m_vVelocity[1] * 50;
		if (d > 0) m_vForceSum[0] -= d;
	}
		
	if (m_vPosition[0] + 5 < 1)
	{
		float d = 1 - (m_vPosition[0] + 5);
		d *= 4000;
		d += m_vVelocity[1] * 50;
		if (d > 0) m_vForceSum[0] += d;
	}*/
}

void RigidBody::DoPhysicMove(float DeltaTime, float direction)
{
	Vector3 tmp(m_vForceSum * DeltaTime);

	m_vQuantityOfMotion += tmp;

	tmp = m_vMomentumSum * DeltaTime;
	m_vAngularMomentum += tmp;
	m_vVelocity = m_vQuantityOfMotion / m_fMass;

	tmp = m_vVelocity * DeltaTime;
	m_vPosition += tmp;

	//MatriceOp::Rotate<MatriceOp::ToObjSpace>(m_mRotationMatrix, m_vAngularMomentum, m_vAngularVelocity);

	m_vAngularVelocity.SetX(m_vAngularVelocity.getX() / m_vInertia.getX());
	m_vAngularVelocity.SetY(m_vAngularVelocity.getY() / m_vInertia.getY());
	m_vAngularVelocity.SetZ(m_vAngularVelocity.getZ() / m_vInertia.getZ());

	Quaternion Rot(1, m_vAngularVelocity.getX()*DeltaTime / 2, m_vAngularVelocity.getY()*DeltaTime / 2, m_vAngularVelocity.getZ()*DeltaTime / 2);

	Rot.Normalize();
	m_qRotation = m_qRotation * Rot;
	m_qRotation.Normalize();
	//MatriceOp::Rotate<MatriceOp::ToWorldSpace>(m_mRotationMatrix, m_vAngularVelocity, m_vAngularVelocity);

	m_mRotationMatrix = m_qRotation.ToMatrix();

	Vector3 mk_vBallVelocity = Vector3(direction, 0.0f, 0.0f);
	m_vForceSum = mk_vBallVelocity * m_fMass;

	//movimento laterale sul terreno
	//5 è il raggio
	//if (m_vPosition[1] + 5 < 1) {
	//	float d = 1 - (m_vPosition[1] + 5);
	//	d *= 4000;
	//	d -= m_vVelocity[1] * 100;
	//	if (d > 0) m_vForceSum[1] += d;
	//}

	/*if (5 - m_vPosition[0] < 1) {
	float d = 1 - (5 - m_vPosition[0]);
	d *= 4000;
	d -= m_vVelocity[1] * 50;
	if (d > 0) m_vForceSum[0] -= d;
	}

	if (m_vPosition[0] + 5 < 1)
	{
	float d = 1 - (m_vPosition[0] + 5);
	d *= 4000;
	d += m_vVelocity[1] * 50;
	if (d > 0) m_vForceSum[0] += d;
	}*/
}

void RigidBody::ApplyForce(const Vector3& force, const Vector3& pointOfApplication)
{
	//SumForceToTotalForce(force);
	//Vector3 ForceOnPoint(pointOfApplication-m_vPosition);
	//VectorialProduct(ForceOnPoint, force, ForceOnPoint);
	//SumMomentumToTotalMomentum(ForceOnPoint);
}

void RigidBody::SumForceToTotalForce(const Vector3& force)
{
	m_vForceSum += force;
}

void RigidBody::SumMomentumToTotalMomentum(const Vector3& momentum)
{
	m_vMomentumSum += momentum;
}

void RigidBody::AttachCollider(Collider* Collider)
{
	m_cCollider = Collider;
}

void RigidBody::DetachCollider()
{
	delete m_cCollider;
}

void RigidBody::SetColliderType(int collidertype)
{
	m_iColliderType = collidertype;
}

int RigidBody::GetColliderType() const
{
	return m_iColliderType;
}


int RigidBody::GetID() const
{
	return m_iID;
}

float RigidBody::GetMass() const
{
	return m_fMass;
}

const Matrix<3, 3>& RigidBody::GetRotationMatrix() const
{
	return m_mRotationMatrix;
}

const Quaternion& RigidBody::GetRotationQuaternion() const
{
	return m_qRotation;
}

const Vector3& RigidBody::GetPosition() const
{
	return m_vPosition;
}

Vector3 RigidBody::GetVelocity() const
{
	return m_vVelocity;
}

Collider* RigidBody::GetCollider() const
{
	return m_cCollider;
}

void RigidBody::SetVelocity(const Vector3& NewVelocity)
{
	m_vVelocity = NewVelocity;
}

void RigidBody::SetPosition(const Vector3& NewPosition)
{
	m_vPosition = NewPosition;
}
#include "RigidBody.h"
/*
void Print(const Vector3& v)
{
	std::cout << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")" << std::endl;
}

void Print(const Quaternion& v)
{
	std::cout << "(" << v.GetValue(0) << ", " << v.GetValue(1) << ", " << v.GetValue(2) << ", " << v.GetValue(3) << ")" << std::endl;
}

void Print(const Matrix<3, 3>& m)
{
	std::cout << m.GetElementAt(0) << ", " << m.GetElementAt(1) << ", " << m.GetElementAt(2) << std::endl;
	std::cout << m.GetElementAt(3) << ", " << m.GetElementAt(4) << ", " << m.GetElementAt(5) << std::endl;
	std::cout << m.GetElementAt(6) << ", " << m.GetElementAt(7) << ", " << m.GetElementAt(8) << std::endl;
}*/

RigidBody::RigidBody(const Vector3& pos, int id, float mass,const Vector3& inertia) : m_vPosition(pos), m_iID(id), m_fMass(mass)
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
}

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
/*
void RigidBody::PrintStatus()
{
	std::cout << "----------------------------- \n" << std::endl;
	std::cout << "RigidBody: " << m_iID << std::endl;
	std::cout << "Mass: " << m_fMass << std::endl;
	std::cout << "Position: ";
	Print(m_vPosition);
	std::cout << "Velocity: ";
	Print(m_vVelocity);
	std::cout << "Inertia: ";
	Print(m_vInertia);
	std::cout << "AngularVelocity: ";
	Print(m_vAngularVelocity);
	std::cout << "QuantityOfMotion: ";
	Print(m_vQuantityOfMotion);
	std::cout << "AngularMomentum: ";
	Print(m_vAngularMomentum);
	std::cout << "ForceSum: ";
	Print(m_vForceSum);
	std::cout << "MomentumSum: ";
	Print(m_vMomentumSum);
	std::cout << "Rotation: ";
	Print(m_qRotation);
	std::cout << "RotationMatrix: \n";
	Print(m_mRotationMatrix);
	std::cout << "----------------------------- \n" << std::endl;
}*/

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
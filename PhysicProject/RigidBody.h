#pragma once

#include "Matrix.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Physic.h"


template<int row, int col>
class Matrix;

class Collider;
class RigidBody
{

public:
	RigidBody(const Vector3& pos, int id, float mass, const Vector3& inertia);
	RigidBody(const RigidBody& other);
	~RigidBody();

	void DoPhysicJump(float DeltaTime);
	void DoPhysicMove(float DeltaTime, float direction);
	void ApplyForce(const Vector3& force, const Vector3& pointOfApplication);
	void SumForceToTotalForce(const Vector3&);
	void SumMomentumToTotalMomentum(const Vector3&);
	void AttachCollider(Collider*);
	void DetachCollider();
	
	void SetColliderType(int collidertype);
	int GetColliderType() const;
	int GetID() const;
	float GetMass() const;
	const Matrix<3, 3>& GetRotationMatrix() const;
	const Quaternion& GetRotationQuaternion() const;
	const Vector3& GetPosition() const;
	Vector3 GetVelocity() const;
	Collider* GetCollider() const;

	void SetPosition(const Vector3&);
	void SetVelocity(const Vector3&);


	enum ColliderTypeEnum : int {
		SPHERE = 0,
		BOX = 1
	};

private:
	float m_fMass;
	Vector3 m_vPosition;
	Vector3 m_vVelocity;
	Vector3 m_vInertia;
	Vector3 m_vAngularVelocity;
	Vector3 m_vQuantityOfMotion;
	Vector3 m_vAngularMomentum;
	Vector3 m_vForceSum;
	Vector3 m_vMomentumSum;
	Quaternion m_qRotation;
	Matrix<3,3> m_mRotationMatrix;
	Collider* m_cCollider;
	int m_iColliderType;
	int m_iID;
};
#pragma once

#include "Collider.h"

class Quaternion;
class RigidBody;
class BoxCollider : public Collider
{
public:
	//BoxCollider(const Vector3& pos, const Vector3& displ, const Quaternion& Rot);
	//BoxCollider(const Vector3& pos, const Vector3& displ, const Quaternion& Rot, const Vector3& dimensions);

	BoxCollider(const Vector3& pos, const Quaternion& Rot);
	BoxCollider(const Vector3& pos, const Quaternion& Rot, const Vector3& dimensions);

	//static const int getType();
	const Quaternion& GetRotation() const;
	const Vector3& GetAxis(int i) const;
	const Vector3& GetFirstAxis();
	const Vector3& GetSecondAxis();
	const Vector3& GetThirdAxis();
	const Vector3& GetHalfSize() const;
	float GetSecondSize() const;
	float GetThirdSize() const;

private:
	//static const int mk_iBoxColliderType;
	const Quaternion* mk_qRotation;
	Vector3 m_vCenter;
	Vector3 m_vHalfSize;
	Vector3 m_vAxises[3];
};
#include "BoxCollider.h"

/*#include "ColliderUtil.h"
#include "RigidBody.h"*/

/*const int BoxCollider::mk_iBoxColliderType = ColliderType::TypeIndex::BOX;

const int BoxCollider::getType()
{
	return BoxCollider::mk_iBoxColliderType;
}

BoxCollider::BoxCollider(const Vector3& pos, const Vector3& displ, const Quaternion& Rot)
	:Collider(mk_iBoxColliderType, displ)
	{
	m_vAxises[0] = Vector3(1,0,0);
	m_vAxises[1] = Vector3(0,1,0);
	m_vAxises[2] = Vector3(0,0,1);
	m_vHalfSize = Vector3(1, 1, 1);
	SetPosition(pos);
	mk_qRotation = &Rot;
	};

BoxCollider::BoxCollider(const Vector3& pos, const Vector3& displ,const Quaternion& Rot,const Vector3& dimensions)
		:Collider(mk_iBoxColliderType, displ), m_vHalfSize(dimensions)
			{
				m_vAxises[0] = Vector3(1, 0, 0);
				m_vAxises[1] = Vector3(0, 1, 0);
				m_vAxises[2] = Vector3(0, 0, 1);
				SetPosition(pos);
				mk_qRotation = &Rot;
			};
			*/
BoxCollider::BoxCollider(const Vector3& pos, const Quaternion& Rot)
	:Collider()
{
	m_vAxises[0] = Vector3(1, 0, 0);
	m_vAxises[1] = Vector3(0, 1, 0);
	m_vAxises[2] = Vector3(0, 0, 1);
	m_vHalfSize = Vector3(1, 1, 1);
	SetPosition(pos);
	mk_qRotation = &Rot;
};

BoxCollider::BoxCollider(const Vector3& pos, const Quaternion& Rot, const Vector3& dimensions)
	:Collider(), m_vHalfSize(dimensions)
{
	m_vAxises[0] = Vector3(1, 0, 0);
	m_vAxises[1] = Vector3(0, 1, 0);
	m_vAxises[2] = Vector3(0, 0, 1);
	SetPosition(pos);
	mk_qRotation = &Rot;
};


const Vector3& BoxCollider::GetFirstAxis() 
{
	return m_vAxises[0];
};

const Vector3& BoxCollider::GetSecondAxis() 
{
	return m_vAxises[1];
};

const Vector3& BoxCollider::GetThirdAxis() 
{
	return m_vAxises[2];
};

const Vector3& BoxCollider::GetHalfSize() const
{
	return m_vHalfSize;
};

float BoxCollider::GetSecondSize() const
{
	return m_vHalfSize.getY();
};

float BoxCollider::GetThirdSize() const
{
	return m_vHalfSize.getZ();
};

const Vector3& BoxCollider::GetAxis(int i) const
{
	return m_vAxises[i];
};

const Quaternion& BoxCollider::GetRotation() const
{
	return *mk_qRotation;
};
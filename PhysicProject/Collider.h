#pragma once

#include "Vector3.h"

class Collider abstract
{

public:
	int GetType() const;
	const Vector3 GetWorldPosition() const;

protected:
	//Collider(int type, const Vector3& displ);
	Collider();
	void SetPosition(const Vector3& pos);

private:
	int m_iType;
	Vector3 m_vDisplacement;
	const Vector3* mk_vPosition;
};
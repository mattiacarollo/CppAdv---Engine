#pragma once

#include "Vector3.h"

class Collider abstract
{

public:
	const Vector3 GetWorldPosition() const;

protected:
	//Collider(const Vector3& displ);
	Collider();
	void SetPosition(const Vector3& pos);

private:
	//Vector3 m_vDisplacement;
	const Vector3* mk_vPosition;
};
#pragma once

#include "Vector3.h"

class Collider abstract
{

public:
	const Vector3 GetWorldPosition() const;

protected:
	Collider();
	void SetPosition(const Vector3& pos);

private:
	const Vector3* mk_vPosition;
};
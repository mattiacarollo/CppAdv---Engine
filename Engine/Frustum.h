#pragma once
#include <DirectXMath.h>

using namespace DirectX;
class Frustum
{
public:
	Frustum();
	Frustum(const Frustum&);
	~Frustum();

	void ConstructFrustum(float, DirectX::XMMATRIX&, DirectX::XMMATRIX&);

	bool CheckPoint(float, float, float);
	bool CheckCube(float, float, float, float);
	bool CheckSphere(float, float, float, float);
	bool CheckRectangle(float, float, float, float, float, float);

private:
	DirectX::XMVECTOR m_planes[6];
};

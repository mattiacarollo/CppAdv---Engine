#include "Camera.h"
#include <algorithm>

using namespace utility;
using namespace DirectX;

Camera::Camera()
	: mFocusPoint(XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f))
	, mPhi(0.0f)
	, mTheta(XM_PIDIV2)
	, mRho(10)
{}


XMMATRIX Camera::getViewMatrix() const
{
	XMVECTOR up = { 0.0f, 1.0f, 0.0f, 0.0f };
	return XMMatrixLookAtLH(getCameraPosition(), mFocusPoint, up);
}

XMVECTOR Camera::getCameraPosition() const
{
	const float cosPhi = std::cos(mPhi);
	const float sinPhi = std::sin(mPhi);
	const float cosTheta = std::cos(mTheta);
	const float sinTheta = std::sin(mTheta);
	XMVECTOR ret =
	{
		mRho * sinTheta * sinPhi,
		mRho * cosTheta,
		-mRho * sinTheta * cosPhi,
		0.0f
	};

	return XMVectorAdd(ret, mFocusPoint);
}

XMFLOAT4 Camera::getCameraPositionFlaot4() const
{
	XMFLOAT4 ret;
	XMStoreFloat4(&ret, getCameraPosition());
	return ret;
}

void Camera::xRotation(const float dTheta)
{
	mTheta += dTheta;
	adjustTheta();
}

void Camera::yRotation(const float dPhi)
{
	mPhi += dPhi;
	adjustPhi();
}

void Camera::translate(const float dRho)
{
	mRho += dRho;
	adjustRho();
}

void Camera::setFocusPoint(const DirectX::XMVECTOR focusPoint)
{
	mFocusPoint = focusPoint;
}

void Camera::adjustTheta()
{
	mTheta = std::min(std::max(mTheta, 0.1f), (XM_PI - 0.1f));
}

void Camera::adjustPhi()
{
	float div = std::floor(std::abs(mPhi / XM_2PI)); //std::trunc
	if (mPhi > 0.0f)
		mPhi -= div * XM_2PI;
	else
		mPhi += (div + 1.0f) * XM_2PI;
}

void Camera::adjustRho()
{
	if (mRho < 0.01f)
		mRho = 0.01f;
}

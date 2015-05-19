#pragma once

#include <DirectXMath.h>
#include <algorithm>

namespace utility
{
	class Camera
	{
	public:
		Camera();

		DirectX::XMMATRIX getViewMatrix() const;
		DirectX::XMVECTOR getCameraPosition() const;
		DirectX::XMFLOAT4 getCameraPositionFlaot4() const;

		void setFocusPoint(const DirectX::XMVECTOR focusPoint);

		void xRotation(const float dTheta);
		void yRotation(const float dPhi);
		void translate(const float dRho);

	private:
		void adjustTheta();
		void adjustPhi();
		void adjustRho();

		DirectX::XMVECTOR mFocusPoint;
		float mPhi;
		float mTheta;
		float mRho;
	};
}

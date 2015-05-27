#include "Frustum.h"

Frustum::Frustum()
{
}


Frustum::Frustum(const Frustum& other)
{
}


Frustum::~Frustum()
{
}


void Frustum::ConstructFrustum(float screenDepth, DirectX::XMMATRIX& projectionMatrix, DirectX::XMMATRIX& viewMatrix)
{
	float zMinimum, r;
	DirectX::XMMATRIX matrix;

	DirectX::XMFLOAT4X4 projectionFloat;
	DirectX::XMStoreFloat4x4(&projectionFloat, projectionMatrix);	
	// Calculate the minimum Z distance in the frustum.
	zMinimum = -projectionFloat._43 / projectionFloat._33;
	r = screenDepth / (screenDepth - zMinimum);
	projectionFloat._33 = r;
	projectionFloat._43 = -r * zMinimum;

	projectionMatrix = DirectX::XMLoadFloat4x4(&projectionFloat);
		
	// Create the frustum matrix from the view matrix and updated projection matrix.
	//D3DXMatrixMultiply(&matrix, &viewMatrix, &projectionMatrix);
	matrix = XMMatrixMultiply(viewMatrix, projectionMatrix);

	DirectX::XMFLOAT4X4 matrixFloat;
	DirectX::XMStoreFloat4x4(&matrixFloat, matrix);

	// Calculate near plane of frustum.
	DirectX::XMFLOAT4 float4;
	DirectX::XMStoreFloat4(&float4, m_planes[0]);

	float4.x = matrixFloat._14 + matrixFloat._13;
	float4.y = matrixFloat._24 + matrixFloat._23;
	float4.z = matrixFloat._34 + matrixFloat._33;
	float4.w = matrixFloat._44 + matrixFloat._43;

	m_planes[0] = DirectX::XMLoadFloat4( &float4 );
	//D3DXPlaneNormalize(&m_planes[0], &m_planes[0]);
	m_planes[0] = DirectX::XMPlaneNormalize(m_planes[0]);

	DirectX::XMStoreFloat4(&float4, m_planes[1]);

	float4.x = matrixFloat._14 + matrixFloat._13;
	float4.y = matrixFloat._24 + matrixFloat._23;
	float4.z = matrixFloat._34 + matrixFloat._33;
	float4.w = matrixFloat._44 + matrixFloat._43;

	m_planes[1] = DirectX::XMLoadFloat4(&float4);
	//D3DXPlaneNormalize(&m_planes[1], &m_planes[1]);
	m_planes[1] = DirectX::XMPlaneNormalize(m_planes[1]);

	// Calculate left plane of frustum.
	DirectX::XMStoreFloat4(&float4, m_planes[2]);

	float4.x = matrixFloat._14 + matrixFloat._11;
	float4.y = matrixFloat._24 + matrixFloat._21;
	float4.z = matrixFloat._34 + matrixFloat._31;
	float4.w = matrixFloat._44 + matrixFloat._41;

	m_planes[2] = DirectX::XMLoadFloat4(&float4);
	//D3DXPlaneNormalize(&m_planes[2], &m_planes[2]);
	m_planes[2] = DirectX::XMPlaneNormalize(m_planes[2]);

	// Calculate right plane of frustum.
	DirectX::XMStoreFloat4(&float4, m_planes[3]);

	float4.x = matrixFloat._14 + matrixFloat._11;
	float4.y = matrixFloat._24 + matrixFloat._21;
	float4.z = matrixFloat._34 + matrixFloat._31;
	float4.w = matrixFloat._44 + matrixFloat._41;

	m_planes[3] = DirectX::XMLoadFloat4(&float4);
	//D3DXPlaneNormalize(&m_planes[3], &m_planes[3]);
	m_planes[3] = DirectX::XMPlaneNormalize(m_planes[3]);

	// Calculate top plane of frustum.
	DirectX::XMStoreFloat4(&float4, m_planes[4]);

	float4.x = matrixFloat._14 + matrixFloat._12;
	float4.y = matrixFloat._24 + matrixFloat._22;
	float4.z = matrixFloat._34 + matrixFloat._32;
	float4.w = matrixFloat._44 + matrixFloat._42;

	m_planes[4] = DirectX::XMLoadFloat4(&float4);
	//D3DXPlaneNormalize(&m_planes[4], &m_planes[4]);
	m_planes[4] = DirectX::XMPlaneNormalize(m_planes[4]);

	// Calculate bottom plane of frustum.
	DirectX::XMStoreFloat4(&float4, m_planes[5]);

	float4.x = matrixFloat._14 + matrixFloat._12;
	float4.y = matrixFloat._24 + matrixFloat._22;
	float4.z = matrixFloat._34 + matrixFloat._32;
	float4.w = matrixFloat._44 + matrixFloat._42;

	m_planes[5] = DirectX::XMLoadFloat4(&float4);
	//D3DXPlaneNormalize(&m_planes[5], &m_planes[5]);
	m_planes[5] = DirectX::XMPlaneNormalize(m_planes[5]);
	
	return;
}


bool Frustum::CheckPoint(float x, float y, float z)
{
	//int i;
	//DirectX::XMFLOAT3 position= DirectX::XMFLOAT3(x, y, z);

	//// Check if the point is inside all six planes of the view frustum.
	//for (i = 0; i<6; i++)
	//{
	//	DirectX::XMVECTOR PlaneDotProduct = DirectX::XMPlaneDotCoord(m_planes[i], DirectX::XMLoadFloat3(&position));
	//	
	//	if (DirectX::XMVectorGetX(PlaneDotProduct) < 0.0f)
	//	{
	//		return false;
	//	}
	//}

	return true;
}

//bool Frustum::CheckCube(float xCenter, float yCenter, float zCenter, float radius)
//{
//	// Check if any one point of the cube is in the view frustum.
//	for (int i = 0; i < 6; i++)
//	{
//		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter - radius), (yCenter - radius), (zCenter - radius), 1.0f))).vector4_f32[0] >= 0.0f)
//		{
//			continue;
//		}
//
//		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter + radius), (yCenter - radius), (zCenter - radius), 1.0f))).vector4_f32[0] >= 0.0f)
//		{
//			continue;
//		}
//
//		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter - radius), (yCenter + radius), (zCenter - radius), 1.0f))).vector4_f32[0] >= 0.0f)
//		{
//			continue;
//		}
//
//		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter + radius), (yCenter + radius), (zCenter - radius), 1.0f))).vector4_f32[0] >= 0.0f)
//		{
//			continue;
//		}
//
//		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter - radius), (yCenter - radius), (zCenter + radius), 1.0f))).vector4_f32[0] >= 0.0f)
//		{
//			continue;
//		}
//
//		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter + radius), (yCenter - radius), (zCenter + radius), 1.0f))).vector4_f32[0] >= 0.0f)
//		{
//			continue;
//		}
//
//		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter - radius), (yCenter + radius), (zCenter + radius), 1.0f))).vector4_f32[0] >= 0.0f)
//		{
//			continue;
//		}
//
//		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter + radius), (yCenter + radius), (zCenter + radius), 1.0f))).vector4_f32[0] >= 0.0f)
//		{
//			continue;
//		}
//
//		return false;
//	}
//
//	return true;
//}

bool Frustum::CheckCube(float xCenter, float yCenter, float zCenter, float radius)
{
	int i;
	
	DirectX::XMFLOAT3 position;

	// Check if any one point of the cube is in the view frustum.
	for (i = 0; i<6; i++)
	{
		position = DirectX::XMFLOAT3((xCenter - radius), (yCenter - radius), (zCenter - radius));
		if (DirectX::XMVectorGetX( DirectX::XMPlaneDotCoord(m_planes[i], DirectX::XMLoadFloat3(&position)) ) >= 0.0f)
		{
			continue;
		}
		position = DirectX::XMFLOAT3((xCenter + radius), (yCenter - radius), (zCenter - radius));
		if (DirectX::XMVectorGetX(DirectX::XMPlaneDotCoord(m_planes[i], DirectX::XMLoadFloat3(&position))) >= 0.0f)
		{
			continue;
		}

		position = DirectX::XMFLOAT3((xCenter - radius), (yCenter + radius), (zCenter - radius));
		if (DirectX::XMVectorGetX(DirectX::XMPlaneDotCoord(m_planes[i], DirectX::XMLoadFloat3(&position))) >= 0.0f)
		{
			continue;
		}

		position = DirectX::XMFLOAT3((xCenter + radius), (yCenter + radius), (zCenter - radius));
		if (DirectX::XMVectorGetX(DirectX::XMPlaneDotCoord(m_planes[i], DirectX::XMLoadFloat3(&position))) >= 0.0f)
		{
			continue;
		}

		position = DirectX::XMFLOAT3((xCenter - radius), (yCenter - radius), (zCenter + radius));
		if (DirectX::XMVectorGetX(DirectX::XMPlaneDotCoord(m_planes[i], DirectX::XMLoadFloat3(&position))) >= 0.0f)
		{
			continue;
		}
		//
		position = DirectX::XMFLOAT3((xCenter + radius), (yCenter - radius), (zCenter + radius));
		if (DirectX::XMVectorGetX(DirectX::XMPlaneDotCoord(m_planes[i], DirectX::XMLoadFloat3(&position))) >= 0.0f)
		{
			continue;
		}

		position = DirectX::XMFLOAT3((xCenter - radius), (yCenter + radius), (zCenter + radius));
		if (DirectX::XMVectorGetX(DirectX::XMPlaneDotCoord(m_planes[i], DirectX::XMLoadFloat3(&position))) >= 0.0f)
		{
			continue;
		}

		position = DirectX::XMFLOAT3((xCenter + radius), (yCenter + radius), (zCenter + radius));
		if (DirectX::XMVectorGetX(DirectX::XMPlaneDotCoord(m_planes[i], DirectX::XMLoadFloat3(&position))) >= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
}


bool Frustum::CheckSphere(float xCenter, float yCenter, float zCenter, float radius)
{
	int i;

	DirectX::XMFLOAT3 position = DirectX::XMFLOAT3(xCenter, yCenter, zCenter);
	// Check if the radius of the sphere is inside the view frustum.
	for (i = 0; i<6; i++)
	{
		if (DirectX::XMVectorGetX(DirectX::XMPlaneDotCoord(m_planes[i], DirectX::XMLoadFloat3(&position))) < -radius)
		{
			return false;
		}
	}

	return true;
}


bool Frustum::CheckRectangle(float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize)
{
	int i;

	DirectX::XMFLOAT3 position;
	// Check if any of the 6 planes of the rectangle are inside the view frustum.
	for (i = 0; i<6; i++)
	{
		position = DirectX::XMFLOAT3((xCenter - xSize), (yCenter - ySize), (zCenter - zSize));
		if (DirectX::XMVectorGetX(DirectX::XMPlaneDotCoord(m_planes[i], DirectX::XMLoadFloat3(&position))) >= 0.0f)
		{
			continue;
		}

		//
		position = DirectX::XMFLOAT3((xCenter + xSize), (yCenter - ySize), (zCenter - zSize));
		if (DirectX::XMVectorGetX(DirectX::XMPlaneDotCoord(m_planes[i], DirectX::XMLoadFloat3(&position))) >= 0.0f)
		{
			continue;
		}

		position = DirectX::XMFLOAT3((xCenter - xSize), (yCenter + ySize), (zCenter - zSize));
		if (DirectX::XMVectorGetX(DirectX::XMPlaneDotCoord(m_planes[i], DirectX::XMLoadFloat3(&position))) >= 0.0f)
		{
			continue;
		}

		position = DirectX::XMFLOAT3((xCenter - xSize), (yCenter - ySize), (zCenter + zSize));
		if (DirectX::XMVectorGetX(DirectX::XMPlaneDotCoord(m_planes[i], DirectX::XMLoadFloat3(&position))) >= 0.0f)
		{
			continue;
		}

		position = DirectX::XMFLOAT3((xCenter + xSize), (yCenter + ySize), (zCenter - zSize));
		if (DirectX::XMVectorGetX(DirectX::XMPlaneDotCoord(m_planes[i], DirectX::XMLoadFloat3(&position))) >= 0.0f)
		{
			continue;
		}

		position = DirectX::XMFLOAT3((xCenter + xSize), (yCenter - ySize), (zCenter + zSize));
		if (DirectX::XMVectorGetX(DirectX::XMPlaneDotCoord(m_planes[i], DirectX::XMLoadFloat3(&position))) >= 0.0f)
		{
			continue;
		}

		position = DirectX::XMFLOAT3((xCenter - xSize), (yCenter + ySize), (zCenter + zSize));
		if (DirectX::XMVectorGetX(DirectX::XMPlaneDotCoord(m_planes[i], DirectX::XMLoadFloat3(&position))) >= 0.0f)
		{
			continue;
		}

		position = DirectX::XMFLOAT3((xCenter + xSize), (yCenter + ySize), (zCenter + zSize));
		if (DirectX::XMVectorGetX(DirectX::XMPlaneDotCoord(m_planes[i], DirectX::XMLoadFloat3(&position))) >= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
}
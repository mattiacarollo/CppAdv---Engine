#include "Light.h"


LightClass::LightClass()
{
}


LightClass::LightClass(const LightClass& other)
{
}


LightClass::~LightClass()
{
}


void LightClass::SetAmbientColor(float red, float green, float blue, float alpha)
{
	m_ambientColor = DirectX::XMFLOAT4(red, green, blue, alpha);
	return;
}


void LightClass::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = DirectX::XMFLOAT4(red, green, blue, alpha);
	return;
}


void LightClass::SetPosition(float x, float y, float z)
{
	m_position = DirectX::XMVectorSet(x, y, z, 0.0f);
	return;
}


void LightClass::SetLookAt(float x, float y, float z)
{
	m_lookAt = DirectX::XMVectorSet(x, y, z, 0.0f);
	return;
}


DirectX::XMFLOAT4 LightClass::GetAmbientColor()
{
	return m_ambientColor;
}


DirectX::XMFLOAT4 LightClass::GetDiffuseColor()
{
	return m_diffuseColor;
}


DirectX::XMVECTOR LightClass::GetPosition()
{
	return m_position;
}


void LightClass::GenerateViewMatrix()
{
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	// Create the view matrix from the three vectors.
	m_viewMatrix = DirectX::XMMatrixLookAtLH(m_position, m_lookAt, up);

	return;
}


void LightClass::GetViewMatrix(DirectX::XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}


void LightClass::GenerateOrthoMatrix(float width, float depthPlane, float nearPlane)
{
	// Create the orthographic matrix for the light.
	m_orthoMatrix=DirectX::XMMatrixOrthographicLH(width, width, nearPlane, depthPlane);

	return;
}


void LightClass::GetOrthoMatrix(DirectX::XMMATRIX& orthoMatrix)
{
	orthoMatrix = m_orthoMatrix;
	return;
}


void LightClass::SetDirection(float x, float y, float z)
{
	m_direction = DirectX::XMFLOAT3(x, y, z);
	return;
}


DirectX::XMFLOAT3 LightClass::GetDirection()
{
	return m_direction;
}
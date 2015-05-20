#pragma once

#include <math.h>
#include "Vector3.h"

class Matrix
{
public:

	inline static void SommaVettori(const Vector3& p3, const Vector3& s3, Vector3& o3)
	{
		o3.SetX(p3.getX() + s3.getX());
		o3.SetY(p3.getY() + s3.getY());
		o3.SetZ(p3.getZ() + s3.getZ());
	}

	inline static void SottraiVettori(const Vector3& p3, const Vector3& s3, Vector3& o3)
	{
		o3.SetX(p3.getX() - s3.getX());
		o3.SetY(p3.getY() - s3.getY());
		o3.SetZ(p3.getZ() - s3.getZ());
	}

	inline static void MoltiplicaVettoreScalare(const Vector3& p3, float s, Vector3& o3)
	{
		o3.SetX(p3.getX() * s);
		o3.SetY(p3.getY() * s);
		o3.SetZ(p3.getZ() * s);
	}

	inline static void DividiVettoreScalare(const Vector3& p3, float s, Vector3& o3)
	{
		o3.SetX(p3.getX() / s);
		o3.SetY(p3.getY() / s);
		o3.SetZ(p3.getZ() / s);
	}
	
	float ProdottoScalare(const Vector3& p3, const Vector3& s3);
	void ProdottoVettoriale(const Vector3& p3, const Vector3& s3, Vector3& o3);
	
	void NormalizzaVettore(const Vector3& p3, Vector3& o3);
	
	void RigaXmatrice(const float *i4x4, const float *Matrice4x4, float *o4x4);
	void MatriceXmatrice(const float *i4x4, const float *Matrice4x4, float *o4x4);
	
	void RuotaAssolute(const float *Matrice3x3, const float *i3, float *o3);
	void RuotaRelative(const float *Matrice3x3, const float *i3, float *o3);
	
	void SommaQuaternioni(const float *p4, const float *s4, float *o4);
	void SottraiQuaternioni(const float *p4, const float *s4, float *o4);
	void MoltiplicaQuaternioni(const float *p4, const float *s4, float *o4);
	float ModuloQuaternione(const float *q4);
	void NormalizzaQuaternione(const float *q4, float *o4);
	void MatriceDaQuaternione(const float *q4, float *Matrice3x3);

private:
	float ModuloVettore(const Vector3& p3);
};
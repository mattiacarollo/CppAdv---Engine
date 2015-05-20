#include "Matrix.h"

float Matrix::ProdottoScalare(const Vector3& p3, const Vector3& s3)
{
	return ((p3.getX() * s3.getX()) + (p3.getY() * s3.getY()) + (p3.getZ() * s3.getZ()));
}

void Matrix::ProdottoVettoriale(const Vector3& p3, const Vector3& s3, Vector3& o3)
{
	o3[0] = (p3.getY() * s3.getZ()) - (p3.getZ() * s3.getY());
	o3[1] = (p3.getZ() * s3.getX()) - (p3.getX() * s3.getZ());
	o3[2] = (p3.getX() * s3.getY()) - (p3.getY() * s3.getX());
}

float Matrix::ModuloVettore(const Vector3& p3)
{
	return (sqrt((p3.getX() * p3.getX()) + (p3.getY() * p3.getY()) + (p3.getZ() * p3.getZ())));
}

void Matrix::NormalizzaVettore(const Vector3& p3, Vector3& o3)
{
	float a = ModuloVettore(p3);
	if (a > 0.000001f) {
		o3.SetX( p3.getX() / a );
		o3.SetY( p3.getY() / a );
		o3.SetZ( p3.getZ() / a );
	}
}


void Matrix::RigaXmatrice(const float *i4x4, const float *Matrice4x4, float *o4x4)
{
	float X = Matrice4x4[0] * i4x4[0] + Matrice4x4[1] * i4x4[4] + Matrice4x4[2] * i4x4[8] + Matrice4x4[3] * i4x4[12];
	float Y = Matrice4x4[4] * i4x4[0] + Matrice4x4[5] * i4x4[4] + Matrice4x4[6] * i4x4[8] + Matrice4x4[7] * i4x4[12];
	float Z = Matrice4x4[8] * i4x4[0] + Matrice4x4[9] * i4x4[4] + Matrice4x4[10] * i4x4[8] + Matrice4x4[11] * i4x4[12];
	float W = Matrice4x4[12] * i4x4[0] + Matrice4x4[13] * i4x4[4] + Matrice4x4[14] * i4x4[8] + Matrice4x4[15] * i4x4[12];
	o4x4[0] = X;
	o4x4[4] = Y;
	o4x4[8] = Z;
	o4x4[12] = W;
}

void Matrix::MatriceXmatrice(const float *i4x4, const float *Matrice4x4, float *o4x4)
{
	RigaXmatrice(&i4x4[0], Matrice4x4, &o4x4[0]);
	RigaXmatrice(&i4x4[1], Matrice4x4, &o4x4[1]);
	RigaXmatrice(&i4x4[2], Matrice4x4, &o4x4[2]);
	RigaXmatrice(&i4x4[3], Matrice4x4, &o4x4[3]);
}


void Matrix::RuotaAssolute(const float *Matrice3x3, const float *i3, float *o3)
{
	float X = i3[0];
	float Y = i3[1];
	float Z = i3[2];
	o3[0] = Matrice3x3[0] * X + Matrice3x3[3] * Y + Matrice3x3[6] * Z;
	o3[1] = Matrice3x3[1] * X + Matrice3x3[4] * Y + Matrice3x3[7] * Z;
	o3[2] = Matrice3x3[2] * X + Matrice3x3[5] * Y + Matrice3x3[8] * Z;
}

void Matrix::RuotaRelative(const float *Matrice3x3, const float *i3, float *o3)
{
	float X = i3[0];
	float Y = i3[1];
	float Z = i3[2];
	o3[0] = Matrice3x3[0] * X + Matrice3x3[1] * Y + Matrice3x3[2] * Z;
	o3[1] = Matrice3x3[3] * X + Matrice3x3[4] * Y + Matrice3x3[5] * Z;
	o3[2] = Matrice3x3[6] * X + Matrice3x3[7] * Y + Matrice3x3[8] * Z;
}


void Matrix::SommaQuaternioni(const float *p4, const float *s4, float *o4)
{
	o4[0] = p4[0] + s4[0];
	o4[1] = p4[1] + s4[1];
	o4[2] = p4[2] + s4[2];
	o4[3] = p4[3] + s4[3];
}

void Matrix::SottraiQuaternioni(const float *p4, const float *s4, float *o4)
{
	o4[0] = p4[0] - s4[0];
	o4[1] = p4[1] - s4[1];
	o4[2] = p4[2] - s4[2];
	o4[3] = p4[3] - s4[3];
}

void Matrix::MoltiplicaQuaternioni(const float *p4, const float *s4, float *o4)
{
	float S = p4[0] * s4[0] - p4[1] * s4[1] - p4[2] * s4[2] - p4[3] * s4[3];
	float X = p4[0] * s4[1] + p4[1] * s4[0] + p4[2] * s4[3] - p4[3] * s4[2];
	float Y = p4[0] * s4[2] - p4[1] * s4[3] + p4[2] * s4[0] + p4[3] * s4[1];
	float Z = p4[0] * s4[3] + p4[1] * s4[2] - p4[2] * s4[1] + p4[3] * s4[0];
	o4[0] = S;
	o4[1] = X;
	o4[2] = Y;
	o4[3] = Z;
}

float Matrix::ModuloQuaternione(const float *q4)
{
	return(sqrt((q4[0] * q4[0]) + (q4[1] * q4[1]) + (q4[2] * q4[2]) + (q4[3] * q4[3])));
}

void Matrix::NormalizzaQuaternione(const float *q4, float *o4)
{
	float a = ModuloQuaternione(q4);
	if (a > 0.000001f) {
		o4[0] = q4[0] / a;
		o4[1] = q4[1] / a;
		o4[2] = q4[2] / a;
		o4[3] = q4[3] / a;
	}
}

void Matrix::MatriceDaQuaternione(const float *q4, float *Matrice3x3)
{
	float X2 = q4[1] * q4[1];
	float Y2 = q4[2] * q4[2];
	float Z2 = q4[3] * q4[3];
	float XY = q4[1] * q4[2];
	float XZ = q4[1] * q4[3];
	float YZ = q4[2] * q4[3];
	float SX = q4[0] * q4[1];
	float SY = q4[0] * q4[2];
	float SZ = q4[0] * q4[3];

	Matrice3x3[0] = 1.0f - 2.0f * (Y2 + Z2);
	Matrice3x3[1] = 2.0f * (XY + SZ);
	Matrice3x3[2] = 2.0f * (XZ - SY);
	Matrice3x3[3] = 2.0f * (XY - SZ);
	Matrice3x3[4] = 1.0f - 2.0f * (Z2 + X2);
	Matrice3x3[5] = 2.0f * (YZ + SX);
	Matrice3x3[6] = 2.0f * (XZ + SY);
	Matrice3x3[7] = 2.0f * (YZ - SX);
	Matrice3x3[8] = 1.0f - 2.0f * (X2 + Y2);
}
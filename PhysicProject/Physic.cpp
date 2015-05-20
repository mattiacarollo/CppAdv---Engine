#include "Physic.h"

//La funzione di integrazione. Viene invocata ogni deltaTime secondi
void Physic::DoPhysic(float deltaTime, Vector3& m_vPos, Vector3& m_vVel, Vector3& m_vG, float M)
{
	Vector3 m_vF;
	Vector3 m_vA;

	Matrix::MoltiplicaVettoreScalare(m_vG, M, m_vF);

	//movimento laterale sul terreno
	if (m_vPos[1] + 5 < 1) {
		float d = 1 - (m_vPos[1] + 5);
		d *= 4000;
		d -= m_vVel[1] * 100;
		if (d > 0) m_vF[1] += d;
	}

	if (5 - m_vPos[0] < 1) {
		float d = 1 - (5 - m_vPos[0]);
		d *= 4000;
		d -= m_vVel[1] * 50;
		if (d > 0) m_vF[0] -= d;
	}

	if (m_vPos[0] + 5 < 1)
	{
		float d = 1 - (m_vPos[0] + 5);
		d *= 4000;
		d += m_vVel[1] * 50;
		if (d > 0) m_vF[0] += d;
	}

	//movimento di caduta
	Matrix::DividiVettoreScalare(m_vF, M, m_vA);
	Matrix::MoltiplicaVettoreScalare(m_vA, deltaTime, m_vA);
	Matrix::SommaVettori(m_vVel, m_vA, m_vVel);
	Matrix::MoltiplicaVettoreScalare(m_vVel, deltaTime, m_vA);
	Matrix::SommaVettori(m_vPos, m_vA, m_vPos);
}
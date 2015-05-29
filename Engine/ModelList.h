#pragma once

#include <DirectXMath.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include "GameObject.h"

class ModelListClass
{
private:
	struct ModelInfoType
	{
		DirectX::XMFLOAT4 color;
		float positionX, positionY, positionZ;
	};

public:
	ModelListClass();
	ModelListClass(const ModelListClass&);
	~ModelListClass();

	bool Initialize(int);
	void Shutdown();

	int GetModelCount();
	void GetData(int, float&, float&, float&, DirectX::XMFLOAT4);
	void AddObject(GameObject *gameObject);

private:
	int m_modelCount;
	//ModelInfoType* m_ModelInfoList;
	std::vector<GameObject*> *m_ModelInfoVector; //use vector
};

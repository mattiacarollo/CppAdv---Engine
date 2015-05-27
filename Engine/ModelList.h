#pragma once

#include <DirectXMath.h>
#include <stdlib.h>
#include <time.h>

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

private:
	int m_modelCount;
	ModelInfoType* m_ModelInfoList;
};

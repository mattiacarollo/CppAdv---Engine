#include "ModelList.h"


ModelListClass::ModelListClass()
{
	//m_ModelInfoList = 0;
}


ModelListClass::ModelListClass(const ModelListClass& other)
{
}


ModelListClass::~ModelListClass()
{
}


bool ModelListClass::Initialize(int numModels)
{
	int i;
	float red, green, blue;


	// Store the number of models.
	m_modelCount = numModels;

	// Create a list array of the model information.
	//m_ModelInfoList = new ModelInfoType[m_modelCount];
	m_ModelInfoVector = new std::vector<GameObject*>();
	if (!m_ModelInfoVector)
	{
		return false;
	}

	// Seed the random generator with the current time.
	srand((unsigned int)time(NULL));

	// Go through all the models and randomly generate the model color and position.
	//for (i = 0; i<m_modelCount; i++)
	//{
	//	// Generate a random color for the model.
	//	red = (float)rand() / RAND_MAX;
	//	green = (float)rand() / RAND_MAX;
	//	blue = (float)rand() / RAND_MAX;

	//	m_ModelInfoList[i].color = DirectX::XMFLOAT4(red, green, blue, 1.0f);

	//	// Generate a random position in front of the viewer for the mode.
	//	m_ModelInfoList[i].positionX = rand()%100;//(((float)rand() - (float)rand()) / RAND_MAX) * 10.0f;
	//	m_ModelInfoList[i].positionY = 1.0f;//(((float)rand() - (float)rand()) / RAND_MAX) * 10.0f;
	//	m_ModelInfoList[i].positionZ = rand()%100; ((((float)rand() - (float)rand()) / RAND_MAX) * 10.0f) + 5.0f;
	//}

	return true;
}


void ModelListClass::Shutdown()
{
	// Release the model information list.
	/*if (m_ModelInfoList)
	{
		delete[] m_ModelInfoList;
		m_ModelInfoList = 0;
	}*/

	return;
}


int ModelListClass::GetModelCount()
{
	//return m_modelCount;
	return m_ModelInfoVector->size();
}


void ModelListClass::GetData(int index, float& positionX, float& positionY, float& positionZ, DirectX::XMFLOAT4 color)
{

	m_ModelInfoVector->at(index)->getPosition(positionX, positionY, positionZ);

	/*positionX = m_ModelInfoVector->at(index)-> x;
	positionY = m_ModelInfoVector->at(index)->y  ;
	positionZ = m_ModelInfoVector->at(index)->z  ;*/
	/*positionY = m_ModelInfoList[index].positionY;
	positionZ = m_ModelInfoList[index].positionZ;*/

	//color =  DirectX::XMFLOAT4(2.0f, 2.f, 2.f, 1.0f);

	/*positionX = m_ModelInfoList[index].positionX;
	positionY = m_ModelInfoList[index].positionY;
	positionZ = m_ModelInfoList[index].positionZ;

	color = m_ModelInfoList[index].color;*/

	return;
}


void ModelListClass::AddObject(GameObject *gameObject){
	
	m_ModelInfoVector->push_back(gameObject);
	
}
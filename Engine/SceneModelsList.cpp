#include "SceneModelsList.h"


SceneModelsList::SceneModelsList()
{
}


SceneModelsList::SceneModelsList(const SceneModelsList& other)
{
}


SceneModelsList::~SceneModelsList()
{
}

void SceneModelsList::AddObject(GameObject *gameObject)
{
	m_SceneModelVector.push_back(gameObject);
}


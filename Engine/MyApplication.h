#pragma once


#include "GraphicsManager.h"
#include "GameObject.h"
#include "Physic.h"
#include "Constants.h"
#include <iostream>
#include <vector>


using namespace std;


class MyApplication : public GraphicsManager {

public :
	void start() override;
	void update() override;

	std::vector<GameObject*> m_GameObjectPool;

	GameObject* cube1;
	GameObject* cube2;
	GameObject* cube3;
	GameObject* cube4;
	GameObject* cube5;
};

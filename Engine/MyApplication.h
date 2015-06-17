#pragma once


#include "GraphicsManager.h"
#include "GameObject.h"
#include "Physic.h"
#include <iostream>
#include <vector>


using namespace std;


class MyApplication : public GraphicsManager {

public :
	void start();
	void update(int, XMMATRIX&, XMMATRIX&, XMMATRIX&);

	GameObject* cube;
	GameObject* cube2;
	GameObject* cube3;
	GameObject* cube4;

	Physic p;
};

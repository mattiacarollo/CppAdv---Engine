#include "GraphicsManager.h"
#include "GameObject.h"
#include "Physic.h"
#include <iostream>
#include <vector>


using namespace std;


class MyApplication : public GraphicsManager {

public :
	void start();
	void update();

	GameObject* cube;
	GameObject* cube2;

	Physic p;
};

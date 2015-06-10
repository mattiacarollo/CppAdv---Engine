#include "GraphicsManager.h"
#include "GameObject.h"
#include <iostream>
#include <vector>


using namespace std;


class MyApplication : public GraphicsManager {
private :
	
	
	
public :
	void start();
	void update(float);

	GameObject *cube;
	GameObject *cube2;
};

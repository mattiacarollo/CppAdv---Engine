#include "MyApplication.h"
#include <math.h>    
#include <time.h>


void MyApplication::start(){
	cube = InstanceGameObject(IdModel::cube, IdShader::textureShaderId);
	cube2 = InstanceGameObject(IdModel::cube, IdShader::textureShaderId);

	cube->setPosition(10, 1, 10); //posizione iniziale dell'oggetto
	cube->setScale(1, 1, 1);

	cube2->setPosition(50, 1, 50); //posizione iniziale dell'oggetto
	cube2->setScale(1, 1, 1);

	//vector <GameObject*> *gameCube = new vector<GameObject*>();

	// aggiungo alla coda da processare
	for (int i = 0; i< 10; i++)
	{
		// Generate a random color for the model.
		GameObject* gameObject = InstanceGameObject(IdModel::cube, IdShader::textureShaderId);
		
		// Generate a random position in front of the viewer for the mode.
		gameObject->x = rand() % 100;//(((float)rand() - (float)rand()) / RAND_MAX) * 10.0f;
		gameObject->y = 1.0f;//(((float)rand() - (float)rand()) / RAND_MAX) * 10.0f;
		gameObject->z = rand() % 100; //((((float)rand() - (float)rand()) / RAND_MAX) * 10.0f) + 5.0f;

	}

	
	//addWindows(new GameObject( IdModel::cube, IdShader::textureShaderId ));
	//addWindows(sphere);
}


//verra chiamata ad ogni frame
void MyApplication::update( float deltaTime ){
	
	static float count = 0;
	count += 1.f;

	float angleX = cos(count * DirectX::XM_PI/180); 
	float distance = 1 * (angleX * deltaTime *0.01);
	//cube2->addPosition(angleX * deltaTime* 0.1, 0, 0);
	cube2->x +=  distance ;

	//float angleY = sin(count * DirectX::XM_PI / 180);

	cube->x *= (distance+1);


}
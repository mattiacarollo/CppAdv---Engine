#include "MyApplication.h"


void MyApplication::start(){
	cube = new GameObject(IdModel::cube, IdShader::textureShaderId);
	cube2 = new GameObject(IdModel::cube, IdShader::textureShaderId);

	cube->setPosition(0, 2, 3); //posizione iniziale dell'oggetto
	cube->setScale(1, 1, 1);

	cube2->setPosition(10, 10, 3); //posizione iniziale dell'oggetto
	cube2->setScale(1, 1, 1);
	// aggiungo alla coda da processare
	addWindows(cube);
	addWindows(cube2);
	//addWindows(sphere);
}


//verra chiamata ad ogni frame
void MyApplication::update(){
	//static int count = 0;
	//count++;
	//if (cube){
	//	//m_ListVector
	//	cube->setPosition(count, 0,0);
	//}

}
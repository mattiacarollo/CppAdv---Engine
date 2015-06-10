#include "MyApplication.h"
#include <math.h>    
#include <time.h>


void MyApplication::start(){

	cube = InstanceGameObject(); // Primo oggetto con posizione e scala
	cube->addModel(IdModel::cube);
	cube->addShader(IdShader::texture);
	cube->addTexture(IdTexture::ice);
	cube->setPosition(40, 5, 50); 
	cube->setScale(1, 1, 1);

	cube2 = InstanceGameObject(); // Secondo oggetto con posizione e scala
	cube->addModel(IdModel::cube);
	cube->addShader(IdShader::texture);
	cube->addTexture(IdTexture::marble);
	cube2->setPosition(60, 5, 50);
	cube2->setScale(1, 1, 1);

}


void MyApplication::update(){

}
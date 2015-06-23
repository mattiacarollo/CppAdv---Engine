#include "MyApplication.h"
#include <math.h>    
#include <time.h>


void MyApplication::start(){

	for (int i = 0; i < Constants::MAX_MODELS; ++i)
	{
		GameObject* temp;
		temp = InstanceGameObject();
		temp->addModel(m_CubeModel);
		//temp->setID(i);
		temp->setPosition(rand() % 100, rand() % 10, rand() % 100);
		temp->addShader(IdShader::color);
		temp->setScale(1, 1, 1);
		m_GameObjectPool.push_back(temp);
	}

	cube1 = InstanceGameObject(); // Primo oggetto con posizione e scala
	cube1->addModel(m_SphereModel);
	cube1->addShader(IdShader::color);
	cube1->setPosition(50, 10, 50);
	cube1->setScale(1, 1, 1);
	AddRigidBody(cube1, 0, 5);

	cube2 = InstanceGameObject(); 
	cube2->addModel(m_SphereModel);  
	cube2->addShader(IdShader::texture);
	cube2->addTexture(Constants::METAL);
	cube2->addTexture(Constants::WALL01);
	cube2->setPosition(50, 20, 50);
	cube2->setScale(1, 1, 1);
	AddRigidBody(cube2, 0, 5);

	//cube3 = InstanceGameObject();
	//cube3->addModel(m_CubeModel);
	//cube3->addShader(IdShader::texture);
	//cube3->addTexture(Constants::METAL);
	//cube3->addTexture(Constants::ICE);
	//cube3->setPosition(50, 10, 50 );
	//cube3->setScale(1, 1, 1);
	////AddRigidBody(cube3, 1, 300);
	//
	//cube4 = InstanceGameObject(); 
	//cube4->addModel(m_CubeModel);  
	//cube4->addShader(IdShader::texture);
	//cube4->addTexture(Constants::METAL);
	//cube4->setPosition(60, 10, 50);
	//cube4->setScale(1, 1, 1);
	////AddRigidBody(cube4, 1, 600);

	//cube5 = InstanceGameObject();
	//cube5->addModel(m_CubeModel);
	//cube5->addShader(IdShader::color);
	//cube5->setPosition(70, 10, 50);
	//cube5->setScale(1, 1, 1);
	
}


void MyApplication::update(){
	//static float i = 0;
	//i+= 0.1f;
	//
	//cube5->setPosition(i, cube5->getPosition().y, cube5->getPosition().z);
}
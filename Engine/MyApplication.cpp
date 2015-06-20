#include "MyApplication.h"
#include <math.h>    
#include <time.h>

void MyApplication::start(){

	cube1 = InstanceGameObject(); // Primo oggetto con posizione e scala
	cube1->addModel(m_CubeModel);
	cube1->addShader(IdShader::color);
	cube1->addTexture(Constants::ICE);
	cube1->setPosition(30, 10, 50);
	cube1->setScale(1, 1, 1);
	AddRigidBody(cube1);

	cube2 = InstanceGameObject(); 
	cube2->addModel(m_SphereModel);  
	cube2->addShader(IdShader::texture);
	cube2->addTexture(Constants::METAL);
	cube2->addTexture(Constants::WALL01);
	cube2->setPosition(40, 10, 50);
	cube2->setScale(1, 1, 1);
	AddRigidBody(cube2);

	cube3 = InstanceGameObject();
	cube3->addModel(m_SphereModel);  
	cube3->addShader(IdShader::texture);
	cube3->addTexture(Constants::METAL);
	cube3->addTexture(Constants::ICE);
	cube3->setPosition(50, 10, 50 );
	cube3->setScale(1, 1, 1);
	AddRigidBody(cube3);

	cube4 = InstanceGameObject(); 
	cube4->addModel(m_CubeModel);  
	cube4->addShader(IdShader::texture);
	cube4->addTexture(Constants::METAL);
	//cube4->addTexture(Const::ICE);
	cube4->setPosition(60, 10, 50);
	cube4->setScale(1, 1, 1);
	AddRigidBody(cube4);

	cube5 = InstanceGameObject();
	cube5->addModel(m_CubeModel);
	cube5->addShader(IdShader::texture);
	cube5->addTexture(Constants::METAL);
	//cube4->addTexture(ICE);
	cube5->setPosition(70, 10, 50);
	cube5->setScale(1, 1, 1);
	
}


void MyApplication::update(){
	
	//cube->setPosition( (cube->GetRigidbody()).GetPosition().getX(),
	//	(cube->GetRigidbody()).GetPosition().getY(),
	//	(cube->GetRigidbody()).GetPosition().getZ() );
	//cube2->setPosition((cube2->GetRigidbody()).GetPosition().getX(),
	//	(cube2->GetRigidbody()).GetPosition().getY(),
	//	(cube2->GetRigidbody()).GetPosition().getZ());


}
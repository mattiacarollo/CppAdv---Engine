#include "MyApplication.h"
#include <math.h>    
#include <time.h>


void MyApplication::start(){

	cube = InstanceGameObject(); // Primo oggetto con posizione e scala
	cube->addModel(m_SphereModel);
	cube->addShader(IdShader::color);
	cube->addTexture(ICE);
	cube->setPosition(30, 10, 50);
	cube->setScale(1, 1, 1);
	AddRigidBody(cube);

	cube2 = InstanceGameObject(); 
	cube2->addModel(m_SphereModel);  
	cube2->addShader(IdShader::texture);
	cube2->addTexture(METAL);
	cube2->addTexture(WALL01);
	cube2->setPosition(40, 10, 50);
	cube2->setScale(1, 1, 1);
	AddRigidBody(cube2);

	cube3 = InstanceGameObject();
	cube3->addModel(m_CubeModel);
	cube3->addShader(IdShader::texture);
	cube3->addTexture(METAL);
	cube3->addTexture(ICE);
	cube3->setPosition(50, 10, 50 );
	cube3->setScale(1, 1, 1);
	AddRigidBody(cube3);

	cube4 = InstanceGameObject(); 
	cube4->addModel(m_CubeModel);  
	cube4->addShader(IdShader::depth);
	cube4->addTexture(METAL);
	cube4->addTexture(ICE);
	cube4->setPosition(60, 10, 50);
	cube4->setScale(1, 1, 1);
	AddRigidBody(cube4);
}


void MyApplication::update(){
	
	//cube->setPosition( (cube->GetRigidbody()).GetPosition().getX(),
	//	(cube->GetRigidbody()).GetPosition().getY(),
	//	(cube->GetRigidbody()).GetPosition().getZ() );
	//cube2->setPosition((cube2->GetRigidbody()).GetPosition().getX(),
	//	(cube2->GetRigidbody()).GetPosition().getY(),
	//	(cube2->GetRigidbody()).GetPosition().getZ());


}
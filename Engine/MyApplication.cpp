#include "MyApplication.h"
#include <math.h>    
#include <time.h>


void MyApplication::start(){

	cube = InstanceGameObject(); // Primo oggetto con posizione e scala
	cube->addModel(m_CubeModel);
	cube->addShader(IdShader::color);
	cube->addTexture(ICE);
	cube->setPosition(40, 5, 50); 
	cube->setScale(1, 1, 1);
	cube->AddRigidBody();

	p.AddRigidBody(cube->GetRigidbody(), (cube->GetRigidbody()).GetID());

	cube2 = InstanceGameObject(); // Secondo oggetto con posizione e scala
	cube2->addModel(m_SphereModel);  // è un casino farlo con enum
	cube2->addShader(IdShader::depth);
	cube2->addTexture(METAL);
	cube2->setPosition(60, 5, 50);
	cube2->setScale(1, 1, 1);
	cube2->AddRigidBody();

	p.AddRigidBody(cube2->GetRigidbody(), (cube2->GetRigidbody()).GetID());

	cube3 = InstanceGameObject(); // Terzo oggetto con posizione e scala
	cube3->addModel(m_SphereModel);  // è un casino farlo con enum
	cube3->addShader(IdShader::depth);
	cube3->addTexture(METAL);
	cube3->setPosition(60, 10, 50);
	cube3->setScale(1, 1, 1);
	cube3->AddRigidBody();

	p.AddRigidBody(cube3->GetRigidbody(), (cube3->GetRigidbody()).GetID());

	cube4 = InstanceGameObject(); // Terzo oggetto con posizione e scala
	cube4->addModel(m_CubeModel);  // è un casino farlo con enum
	cube4->addShader(IdShader::color);
	cube4->addTexture(METAL);
	cube4->setPosition(30, 5, 50);
	cube4->setScale(1, 1, 1);
	cube4->AddRigidBody();

	p.AddRigidBody(cube4->GetRigidbody(), (cube4->GetRigidbody()).GetID());
}


void MyApplication::update(int index, XMMATRIX& worldMatrix, XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix){
	m_SceneModelsList->getGameObject(index)->render(worldMatrix, viewMatrix, projectionMatrix);
	p.ComputePhysic();
	cube->setPosition(
		(cube->GetRigidbody()).GetPosition().getX(),
		(cube->GetRigidbody()).GetPosition().getY(),
		(cube->GetRigidbody()).GetPosition().getZ() );
	cube2->setPosition(
		(cube2->GetRigidbody()).GetPosition().getX(),
		(cube2->GetRigidbody()).GetPosition().getY(),
		(cube2->GetRigidbody()).GetPosition().getZ());
	cube3->setPosition(
		(cube3->GetRigidbody()).GetPosition().getX(),
		(cube3->GetRigidbody()).GetPosition().getY(),
		(cube3->GetRigidbody()).GetPosition().getZ());
	cube4->setPosition(
		(cube4->GetRigidbody()).GetPosition().getX(),
		(cube4->GetRigidbody()).GetPosition().getY(),
		(cube4->GetRigidbody()).GetPosition().getZ());
}
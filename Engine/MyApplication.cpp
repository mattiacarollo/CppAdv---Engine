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

	cube3 = InstanceGameObject(); // Terzo oggetto con posizione e scala
	cube3->addModel(m_SphereModel);  // è un casino farlo con enum
	cube3->addShader(IdShader::color);
	cube3->addTexture(METAL);
	cube3->setPosition(60, 10, 50);
	cube3->setScale(1, 1, 1);

}


void MyApplication::update(int index, XMMATRIX& worldMatrix, XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix){
	m_SceneModelsList->getGameObject(index)->render(worldMatrix, viewMatrix, projectionMatrix);
	p.ComputePhysic();
	cube->setPosition(
		(cube->GetRigidbody()).GetPosition().getX(),
		(cube->GetRigidbody()).GetPosition().getY(),
		(cube->GetRigidbody()).GetPosition().getZ() );
}
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
	
	//note: forse per fare la cosa giusta, prima si dovrebbe creare il RigidBody e poi aggiungerlo al modello
	AddRigidBody(cube);

	cube2 = InstanceGameObject(); // Secondo oggetto con posizione e scala
	cube2->addModel(m_SphereModel);  // è un casino farlo con enum
	cube2->addShader(IdShader::texture);
	//cube2->addTexture(METAL);
	//cube2->addTexture(ICE);
	cube2->addTexture(WALL01);
	cube2->setPosition(60, 5, 50);
	cube2->setScale(1, 1, 1);

	cube3 = InstanceGameObject(); // Terzo oggetto con posizione e scala
	cube3->addModel(m_SphereModel);  // è un casino farlo con enum
	cube3->addShader(IdShader::texture);
	cube3->addTexture(METAL);
	cube3->addTexture(ICE);
	cube3->setPosition(60, 10, 50 );
	cube3->setScale(1, 1, 1);

}


void MyApplication::update(){
	
	cube->setPosition( (cube->GetRigidbody()).GetPosition().getX(),
		(cube->GetRigidbody()).GetPosition().getY(),
		(cube->GetRigidbody()).GetPosition().getZ() );


}
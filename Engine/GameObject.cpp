#include "GameObject.h"

GameObject::GameObject(IdModel modelId, IdShader shaderId){
	idModel = modelId;
	idShader = shaderId;

	switch (idModel)
	{
	case cube:
		break;
	case sphere:
		break;
	default:
		break;
	}

	switch (shaderId)
	{
	case coloreShaderId:
		break;
	case textureShaderId:
		break;
	default:
		break;
	}
};

GameObject::~GameObject(){
}


void GameObject::setPosition(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}
void GameObject::setScale(float x, float y, float z){
	this->scaleX = x;
	this->scaleY = y;
	this->scaleZ = z;
}
void GameObject::getPosition(float& x, float& y, float& z){
	x = this->x;
	y = this->y;
	z = this->z;
}
void GameObject::getScale(float& x, float& y, float& z){
	x = this->scaleX;
	y = this->scaleY;
	z = this->scaleZ;
}
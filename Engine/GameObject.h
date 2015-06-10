#pragma once


#include <DirectXMath.h>


using namespace DirectX;

enum IdModel {	cube, sphere, empty };

enum IdShader {	color, depth, texture, shadow, simple, empty };

enum IdTexture {};

class GameObject{
private:

	float scaleX, scaleY, scaleZ;
	

public:
	GameObject(IdModel, IdShader);
	~GameObject();

	void addPosition(float x, float y, float z);
	void setPosition(float x, float y, float z);
	void setScale(float x, float y, float z);
	void getPosition(float& x, float& y, float& z);
	void getScale(float& x, float& y, float& z);

	float x, y, z;
	IdModel idModel;
	IdShader idShader;
};
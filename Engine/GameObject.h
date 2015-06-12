#pragma once


#include "Model.h"
#include "TextureManager.h"
#include "ShaderManager.h"

#include <DirectXMath.h>
#include <vector>
#include "Vector3.h"
#include "RigidBody.h"
#include "SphereCollider.h"


using namespace DirectX;


enum IdShader { color, depth, texture, shadow, simple };


class GameObject{

public:
	GameObject(TextureManager*, ShaderManager*);
	~GameObject();

	void addModel(Model* modelId) { m_idModel = modelId; };
	void addShader(IdShader shaderId) { m_idShader = shaderId; };
	void addTexture(const WCHAR* textureId);

	void setPosition(float x, float y, float z) { m_position = { x, y, z}; };
	void setScale(float x, float y, float z) { m_scale = { x, y, z }; };

	XMFLOAT3 getPosition() const { return m_position; };
	XMFLOAT3 getScale() const { return m_scale; };

	bool render(XMMATRIX&, XMMATRIX&, XMMATRIX&);

	Vector3 SphereInertia(float mass, float radius);
	void AddRigidBody();
	RigidBody& GetRigidbody() const;

private :
	XMFLOAT3 m_position;
	XMFLOAT3 m_scale;
	unsigned int m_Id;

	Model* m_idModel;
	IdShader m_idShader; // serie di if nel render

	std::vector<ID3D11ShaderResourceView*> m_textures;

	TextureManager* m_TextureManager;
	ShaderManager* m_ShaderManager;

	RigidBody* m_pRigidbody;
};
#pragma once


#include <DirectXMath.h>
#include <vector>

using namespace DirectX;

enum IdModel {	cube, sphere };
enum IdShader {	color, depth, texture, shadow, simple };
enum IdTexture { wall01, wall02, ice, metal, terrain, marble };

class GameObject{

public:
	GameObject();
	~GameObject();

	void addModel(IdModel modelId) { m_idModel = modelId; };
	void addShader(IdShader shaderId) { m_idShader = shaderId; };
	void addTexture(IdTexture textureId) { m_idTextures.push_back(textureId); };

	void setPosition(float x, float y, float z) { m_position = { x, y, z}; };
	void setScale(float x, float y, float z) { m_scale = { x, y, z }; };

	XMFLOAT3 getPosition() const { return m_position; };
	XMFLOAT3 getScale() const { return m_scale; };

private :
	XMFLOAT3 m_position;
	XMFLOAT3 m_scale;
	unsigned int m_Id;
	IdModel m_idModel;
	IdShader m_idShader;
	std::vector<IdTexture> m_idTextures;
};
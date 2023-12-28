#pragma once
#include "objfilemodel.h"
#include <d3d11.h>

struct Transform
{
	XMFLOAT3 pos;
	XMFLOAT3 rot;
	XMFLOAT3 scl;

	XMMATRIX GetWorldMaxtrix()
	{
		const XMMATRIX translation = XMMatrixTranslation(pos.x, pos.y, pos.z);
		const XMMATRIX rotation = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
		const XMMATRIX scale = XMMatrixScaling(scl.x, scl.y, scl.z);
		XMMATRIX world = scale * rotation * translation;
		return world;
	}
};

struct CBUFFER0
{
	XMMATRIX WVP;
	XMMATRIX WV;

	XMVECTOR ambientLightColour;
};

struct Material
{

};

class GameObject
{
private:
	// Mesh and D3D stuff
	ObjFileModel* m_ObjectMesh = nullptr;
	ID3D11ShaderResourceView* m_Texture = nullptr;

	// Object position
	Transform m_Transform = 
	{
		{ 0.0f, 0.0f, 0.0f },	// Position
		{ 0.0f, 0.0f, 0.0f },	// Rotation
		{ 1.0f, 1.0f, 1.0f }	// Scale
	};


public:
	GameObject(const char* MeshName, const char* TextureName);
	
	void Draw();
};


#pragma once
#include "objfilemodel.h"

#include "Transform.h"
#include "Material.h"

class GameObject
{
private:
	// Mesh and D3D stuff
	ObjFileModel* m_ObjectMesh = nullptr;
	Material*	  m_Material   = nullptr;

	// Object position
	Transform m_Transform = 
	{
		{ 0.0f, 0.0f, 0.0f },	// Position
		{ 0.0f, 0.0f, 0.0f },	// Rotation
		{ 1.0f, 1.0f, 1.0f }	// Scale
	};


public:
	GameObject(const char* MeshName, const char* MaterialName);
	~GameObject();

	void Update(float deltaTime);

	ObjFileModel* GetMesh() { return m_ObjectMesh; }
	Material*	  GetMaterial() { return m_Material; }
	Transform	  GetTransform() { return m_Transform; }

};


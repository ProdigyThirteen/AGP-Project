#pragma once
#include "objfilemodel.h"

#include "Transform.h"
#include "Material.h"

class Scene;
struct Camera;

class GameObject
{
protected:
	Scene* m_Scene = nullptr;
	
	bool bMarkedForDestruction = false;

	// Mesh and D3D stuff
	ObjFileModel* m_ObjectMesh = nullptr;
	Material*	  m_Material   = nullptr;

	// Object position
	Transform m_Transform = 
	{
		{ 0.0f, 0.0f, 0.0f		 },	// Position
		{ 0.0f, 0.0f, 0.0f, 1.0f },	// Rotation
		{ 1.0f, 1.0f, 1.0f		 }	// Scale
	};

public:
	GameObject(const char* MeshName, const char* MaterialName, Scene* scene);
	virtual ~GameObject();

	virtual void Update(float deltaTime);

	ObjFileModel* GetMesh() { return m_ObjectMesh; }
	Material*	  GetMaterial() { return m_Material; }
	Transform	  GetTransform() { return m_Transform; }

	// Setters
	void		  SetTransform(Transform transform) { m_Transform = transform; }
	void		  SetPosition(DirectX::XMFLOAT3 position) { m_Transform.pos = position; }
	void		  SetRotation(DirectX::XMFLOAT4 rotation) { m_Transform.rot = rotation; }
	void		  SetScale(DirectX::XMFLOAT3 scale) { m_Transform.scl = scale; }

	void Destroy() { bMarkedForDestruction = true; }
	bool IsMarkedForDestruction() { return bMarkedForDestruction; }
};


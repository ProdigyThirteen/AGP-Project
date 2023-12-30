#include "GameObject.h"
#include "MeshDatabase.h"
#include "MaterialDatabase.h"

GameObject::GameObject(const char* MeshName, const char* MaterialName)
{
	m_ObjectMesh = MeshDatabase::GetInstance().GetMesh(MeshName);
	m_Material   = MaterialDatabase::GetInstance().GetMaterial(MaterialName);

	m_Transform.pos = { 0.0f, 0.0f, 5.0f };
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
}

#include "GameObject.h"
#include "MeshDatabase.h"
#include "MaterialDatabase.h"
#include "Camera.h"
#include "InputManager.h"

#include <Keyboard.h>
#include <Mouse.h>
#include "Scene.h"

GameObject::GameObject(const char* MeshName, const char* MaterialName, Scene* scene)
	: m_Scene(scene)
{
	m_ObjectMesh = MeshDatabase::GetInstance().GetMesh(MeshName);
	m_Material   = MaterialDatabase::GetInstance().GetMaterial(MaterialName);
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
}

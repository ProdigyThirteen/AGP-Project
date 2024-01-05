#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "Renderer.h"
#include "Skybox.h"
#include "Player.h"
#include "Collectable.h"

bool Scene::Init(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext)
{
	HRESULT result;

	m_Skybox = new Skybox();
	result = m_Skybox->Init(Device);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to init skybox");
		return false;
	}

	m_Camera = new Camera();

	// Create 20 collectables
	for (int i = 0; i < 20; ++i)
	{
		GameObject* cube = new Collectable("cube", "default");
		m_GameObjects.push_back(cube);
	}

	GameObject* plr = new Player("AIM120D", "missile", m_Camera);
	m_GameObjects.push_back(plr);


	return true;
}

void Scene::AddGameObject(GameObject* gameObject)
{
	m_GameObjectsToAdd.push_back(gameObject);
}

void Scene::RemoveGameObject(GameObject* gameObject)
{
	m_GameObjectsToRemove.push_back(gameObject);
}

void Scene::Update(float deltaTime)
{
	// Handles object updates
	for (auto gameObject : m_GameObjects)
	{
		// Checks if marked for destruction and skips update if true
		if (gameObject->IsMarkedForDestruction())
		{
			OutputDebugString(L"Object marked for destruction\n");
			m_GameObjectsToRemove.push_back(gameObject);
			continue;
		}

		gameObject->Update(deltaTime);
	}

	// Handles adding new objects
	for (auto gameObject : m_GameObjectsToAdd)
	{
		m_GameObjects.push_back(gameObject);
	}
	m_GameObjectsToAdd.clear();

	// Handles removing objects
	for (auto& obj : m_GameObjectsToRemove)
	{
		m_GameObjects.erase(std::remove(m_GameObjects.begin(), m_GameObjects.end(), obj), m_GameObjects.end());
		delete obj;
	}
	m_GameObjectsToRemove.clear();	

	
}

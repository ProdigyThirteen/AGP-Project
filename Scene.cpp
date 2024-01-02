#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "Renderer.h"
#include "Skybox.h"
#include "Player.h"

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
	m_Camera->SetPosition(0.0f, 0.0f, 0.0f);

	// Create basic game objects to visualise world
	GameObject* cube = new GameObject("AIM120D", "missile");
	m_GameObjects.push_back(cube);

	GameObject* plr = new Player("AIM120D", "missile", m_Camera);
	m_GameObjects.push_back(plr);


	return true;
}

void Scene::AddGameObject(GameObject* gameObject)
{
	m_GameObjects.push_back(gameObject);
}

void Scene::Update(float deltaTime)
{
	for (auto gameObject : m_GameObjects)
	{
		gameObject->Update(deltaTime);
	}
}

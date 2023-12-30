#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "Renderer.h"
#include "Skybox.h"

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
	//m_Camera->SetRotation(0.0f, 0.0f);

	return true;
}

void Scene::AddGameObject(GameObject* gameObject)
{
	m_GameObjects.push_back(gameObject);
}

void Scene::Update(float deltaTime)
{
}

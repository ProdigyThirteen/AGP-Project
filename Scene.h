#pragma once

#include <vector>
#include <d3d11.h>

// Forward declarations
class GameObject;
class Camera;
class Skybox;

class Scene
{
private:
	std::vector<GameObject*> m_GameObjects;

	Camera* m_Camera = nullptr;
	Skybox* m_Skybox = nullptr;

public:
	Scene() = default;
	~Scene() = default;

	bool Init(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext);

	void AddGameObject(GameObject* gameObject);

	void Update(float deltaTime);

	Camera* GetCamera() { return m_Camera; }
	Skybox* GetSkybox() { return m_Skybox; }
	std::vector<GameObject*> GetGameObjects() { return m_GameObjects; }
};


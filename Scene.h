#pragma once

#include <SimpleMath.h>
#include <vector>
#include <d3d11.h>
#include <string>

// Forward declarations
class GameObject;
struct Camera;
class Skybox;
class Text;

class Scene
{
private:
	std::vector<GameObject*> m_GameObjects;
	std::vector<GameObject*> m_GameObjectsToAdd;
	std::vector<GameObject*> m_GameObjectsToRemove;

	std::vector<Text*> m_Texts;

	Camera* m_Camera = nullptr;
	Skybox* m_Skybox = nullptr;

	// FPS rendering
	void DrawFPS(float deltaTime);
	int m_FPSTextID = -1;
	float m_FPSTimer = 0.0f;
	int m_FPSCounter = 0;

	// Shitty score system to make this a "game"
	int m_TotalCollectables = 20;
	int m_ScoreTextID = -1;
	int m_Score = 0;

public:
	Scene() = default;
	~Scene();

	bool Init(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext);

	void AddGameObject(GameObject* gameObject);
	void RemoveGameObject(GameObject* gameObject);

	void Update(float deltaTime);

	Camera* GetCamera() { return m_Camera; }
	Skybox* GetSkybox() { return m_Skybox; }
	std::vector<GameObject*> GetGameObjects() { return m_GameObjects; }
	std::vector<Text*> GetText() { return m_Texts; }

	int AddText(DirectX::SimpleMath::Vector2 pos, std::wstring text);
	void RemoveText(int index);
	void UpdateText(int index, std::wstring text);

	// Pretend this is just a level blueprint in Unreal
	void AddScore();
};


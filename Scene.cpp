#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "Renderer.h"
#include "Skybox.h"
#include "Player.h"
#include "Collectable.h"
#include "SoundManager.h"
#include "Text.h"

void Scene::DrawFPS(float deltaTime)
{
    m_FPSTimer += deltaTime;
    ++m_FPSCounter;

    if (m_FPSTimer >= 1.0f)
    {
        std::wstring fps = L"FPS: " + std::to_wstring(m_FPSCounter);
        UpdateText(m_FPSTextID, fps);
        m_FPSTimer = 0.0f;
        m_FPSCounter = 0;
    }
}

Scene::~Scene()
{
	// Delete all game objects
	for (auto& obj : m_GameObjects)
	{
		delete obj;
	}
	m_GameObjects.clear();

	// Delete all texts
	for (auto& text : m_Texts)
	{
		delete text;
	}
	m_Texts.clear();

	delete m_Camera;
	delete m_Skybox;
}

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

    // Create some collectables
    for (int i = 0; i < m_TotalCollectables; ++i)
    {
        GameObject* cube = new Collectable("cube", "default", this);
        m_GameObjects.push_back(cube);
    }

    GameObject* plr = new Player("Spaceship", "Spaceship", m_Camera, this);
    m_GameObjects.push_back(plr);

    SoundManager::GetInstance().PlaySoundEffectInstance("ambient", true);
    SoundManager::GetInstance().SetPersistentAudioVolume(0.25f); // Cheaty way to make the ambient sound quieter

    // Setting up text
    m_FPSTextID = AddText({1150, 0}, L"Hello World!");
    m_ScoreTextID = AddText({ 0, 0 }, L"Score: 0 / " + std::to_wstring(m_TotalCollectables));

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

    DrawFPS(deltaTime);
}

int Scene::AddText(DirectX::SimpleMath::Vector2 pos, std::wstring text)
{
    m_Texts.push_back(new Text(pos, text));
    return m_Texts.size() - 1; // Return index of text to be used as ID
}

void Scene::RemoveText(int index)
{
    m_Texts.erase(m_Texts.begin() + index);
}

void Scene::UpdateText(int index, std::wstring text)
{
    m_Texts[index]->SetText(text);
}

void Scene::AddScore()
{
    m_Score++;
    UpdateText(m_ScoreTextID, L"Score: " + std::to_wstring(m_Score) + L" / " + std::to_wstring(m_TotalCollectables));
}

#include "Game.h"
#include <Windows.h>
#include <d3d11.h>
#include "Globals.h"
#include "Renderer.h"
#include "MeshDatabase.h"
#include "TextureDatabase.h"
#include "ShaderManager.h"
#include "MaterialDatabase.h"

// TODO: Remove
#include "GameObject.h"

Game* Game::instance = nullptr;

LRESULT Game::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_ACTIVATE:
	case WM_ACTIVATEAPP:
	case WM_INPUT:
		// TODO: Handle input
		// Mouse::ProcessMessage(message, wParam, lParam);
		// Keyboard::ProcessMessage(message, wParam, lParam);
		break;

	case WM_SYSKEYDOWN:
		//Keyboard::ProcessMessage(message, wParam, lParam);

	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		//Keyboard::ProcessMessage(message, wParam, lParam);
		break;

	case WM_MOUSEACTIVATE:
		return MA_ACTIVATEANDEAT;

	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		//Mouse::ProcessMessage(message, wParam, lParam);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	//CleanD3D();

	return 0;
}

HRESULT Game::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	this->hInstance = hInstance;

	WNDCLASSEX wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = WindowName;

	if (!RegisterClassEx(&wcex))
	{
		OutputDebugString(L"Failed to register window class\n");
		return E_FAIL;
	}

	RECT rc = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindow(
		WindowName,
		WindowName, 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 
		rc.right - rc.left, 
		rc.bottom - rc.top,
		nullptr, nullptr, 
		hInstance, 
		nullptr);

	if (!hWnd)
	{
		OutputDebugString(L"Failed to create window\n");
		return E_FAIL;
	}

	ShowWindow(hWnd, nCmdShow);

	return S_OK;
}

Game* Game::GetInstance()
{
if (instance == nullptr)
	{
		instance = new Game();
	}

	return instance;
}

bool Game::Init(HINSTANCE hInstance, int nCmdShow)
{
	OutputDebugString(L"Starting game init\n");

	HRESULT hr;
	hr = InitWindow(hInstance, nCmdShow);
	if (FAILED(hr))
	{
		OutputDebugString(L"Failed to init window\n");
		return false;
	}
	OutputDebugString(L"Window initialized\n");

	m_Renderer = new Renderer();
	hr = m_Renderer->Init(hWnd);
	if (FAILED(hr))
	{
		OutputDebugString(L"Failed to init renderer\n");
		return false;
	}
	OutputDebugString(L"Renderer initialized\n");

	// Load assets
	MeshDatabase::GetInstance().LoadMeshes("meshes/", m_Renderer);
	TextureDatabase::GetInstance().LoadTextures("textures/", m_Renderer->GetDevice(), m_Renderer->GetDeviceContext());
	TextureDatabase::GetInstance().CreateSkyboxTexture("skybox01", m_Renderer->GetDevice(), m_Renderer->GetDeviceContext());

	// Create shaders
	ShaderManager::GetInstance().CreateShaders(m_Renderer->GetDevice(), m_Renderer->GetDeviceContext());

	// Create materials from textures and shaders
	MaterialDatabase::GetInstance().CreateNewMaterial("default", "default", "Box");
	MaterialDatabase::GetInstance().CreateSkyboxMaterial("skybox", "skybox", "skybox01");

	// Create scene
	m_Scene = new Scene();
	m_Scene->Init(m_Renderer->GetDevice(), m_Renderer->GetDeviceContext());

	// Add cube to scene
	GameObject* cube = new GameObject("cube", "default");
	m_Scene->AddGameObject(cube);



	bGameOver = false;
	return true;
}

void Game::Run()
{
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_QUIT)
			bGameOver = true;
	}
	else
	{
		m_Renderer->DrawFrame(m_Scene);
	}

}

void Game::Cleanup()
{
	OutputDebugString(L"Starting game cleanup\n");
	delete m_Renderer;
}



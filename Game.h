#pragma once
#include <Windows.h>
#include "Renderer.h"
#include "Scene.h"

class Game
{
private:
	// Singleton instance
	Game() = default;
	Game(const Game&) = delete;	
	Game& operator=(const Game&) = delete;

	static Game* instance;

	// Window handle
	HWND hWnd = { 0 };
	HINSTANCE hInstance = { 0 };
	const wchar_t* WindowName = L"AGP Project Game";

	// Window procedure
	MSG msg = { 0 };
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);

	// State tracking
	bool bGameOver = false;

	// Game components
	Renderer* m_Renderer = nullptr;
	Scene* m_Scene = nullptr;

public:
	~Game() = default;
	static Game* GetInstance();

	bool Init(HINSTANCE hInstance, int nCmdShow);
	void Run();
	void Cleanup();

	bool IsGameOver() { return bGameOver; }
};


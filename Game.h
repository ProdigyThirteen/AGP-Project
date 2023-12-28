#pragma once
#include <Windows.h>
#include "Renderer.h"
#include "MeshDatabase.h"

class Game
{
private:
	// Singleton instance
	Game() = default;
	Game(const Game&) = delete;	
	Game& operator=(const Game&) = delete;

	static Game* instance;

	// Window handle
	HWND hWnd;
	HINSTANCE hInstance;
	const wchar_t* WindowName = L"AGP Project Game";

	// Window procedure
	MSG msg = { 0 };
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);

	// State tracking
	bool bGameOver;

	// Game components
	Renderer* m_Renderer;

public:
	~Game() = default;
	static Game* GetInstance();

	bool Init(HINSTANCE hInstance, int nCmdShow);
	void Run();
	void Cleanup();

	bool IsGameOver() { return bGameOver; }
};


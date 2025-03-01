#include <memory>
#include <Windows.h>

#include "Game.h"


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR cmdLine, _In_ int nCmdShow)
{
	bool result = Game::GetInstance()->Init(hInstance, nCmdShow);
	if (!result)
	{
		return -1;
	}

	while(!Game::GetInstance()->IsGameOver())
	{
		Game::GetInstance()->Run();
	}

	Game::GetInstance()->Cleanup();

	return 0;
}

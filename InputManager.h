#pragma once

#include <Mouse.h>
#include <Keyboard.h>
#include <Windows.h>


class InputManager
{
private:
	InputManager() = default;
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	DirectX::Mouse* m_Mouse = nullptr;
	DirectX::Keyboard* m_Keyboard = nullptr;

	DirectX::Mouse::ButtonStateTracker* m_MouseTracker = nullptr;
	DirectX::Keyboard::KeyboardStateTracker* m_KeyboardTracker = nullptr;

	// Keyboard and mouse state
	DirectX::Mouse::State m_MouseState = { 0 };
	DirectX::Keyboard::State m_KeyboardState = { 0 };
public:

	~InputManager();

	static InputManager& GetInstance()
	{
		static InputManager instance;
		return instance;
	}

	HRESULT Init(HWND hwnd);
	void UpdateStates();

	DirectX::Mouse::State GetMouseState() const { return m_MouseState; }
	DirectX::Keyboard::State GetKeyboardState() const { return m_KeyboardState; }

	DirectX::Keyboard::KeyboardStateTracker* GetKeyboardTracker() const { return m_KeyboardTracker; }
	DirectX::Mouse::ButtonStateTracker* GetMouseTracker() const { return m_MouseTracker; }

};


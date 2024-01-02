#include <Windows.h>
#include "InputManager.h"

#include <Mouse.h>
#include <Keyboard.h>

InputManager::~InputManager()
{
	delete m_Mouse;
	delete m_Keyboard;

	delete m_MouseTracker;
	delete m_KeyboardTracker;
}

HRESULT InputManager::Init(HWND hwnd)
{
    m_Mouse = new DirectX::Mouse();
	m_Keyboard = new DirectX::Keyboard();

	m_MouseTracker = new DirectX::Mouse::ButtonStateTracker();
	m_KeyboardTracker = new DirectX::Keyboard::KeyboardStateTracker();

	if (!m_Mouse || !m_Keyboard || !m_MouseTracker || !m_KeyboardTracker)
	{
		OutputDebugString(L"Failed to create input objects\n");
		return E_FAIL;
	}

	DirectX::Mouse::Get().SetWindow(hwnd);
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::Mode::MODE_RELATIVE);

	OutputDebugString(L"Input objects created\n");

	return S_OK;
}

void InputManager::UpdateStates()
{
	m_KeyboardState = m_Keyboard->GetState();
	m_MouseState	= m_Mouse->GetState();

	m_KeyboardTracker->Update(m_KeyboardState);
	m_MouseTracker->Update(m_MouseState);
}
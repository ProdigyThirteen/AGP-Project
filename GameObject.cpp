#include "GameObject.h"
#include "MeshDatabase.h"
#include "MaterialDatabase.h"
#include "Camera.h"
#include "InputManager.h"

#include <Keyboard.h>
#include <Mouse.h>

//void GameObject::TestCameraTurn()
//{
//	auto mouseState = InputManager::GetInstance().GetMouseState();
//
//	const float m_MouseSensitivity = DirectX::XM_2PI * 0.00025f;
//
//	float xDelta = static_cast<float>(mouseState.x);
//	float yDelta = static_cast<float>(mouseState.y);
//
//	if (xDelta == 0.0f && yDelta == 0.0f)
//		return;
//
//	xDelta *= m_MouseSensitivity;
//	yDelta *= m_MouseSensitivity;
//
//	cam->yaw += xDelta;
//	cam->pitch += yDelta;
//}

//void GameObject::TestFunc()
//{
//	// Handle camera movement
//	auto keyboardState = InputManager::GetInstance().GetKeyboardState();
//
//	// Camera forward vector
//	const DirectX::XMVECTOR lookTo = DirectX::XMVectorSet(sin(cam->yaw) * sin(cam->pitch),
//									 cos(cam->pitch),
//									 cos(cam->yaw)* sin(cam->pitch),
//									 0);
//
//	// Camera right vector
//	const DirectX::XMVECTOR camRight = DirectX::XMVector3Cross(lookTo, DirectX::XMVectorSet(0, 1, 0, 0));
//
//	// Updated input to non globals
//	if (keyboardState.W)
//	{
//		cam->x += DirectX::XMVectorGetX(lookTo) * 0.0001f;
//		cam->y += DirectX::XMVectorGetY(lookTo) * 0.0001f;
//		cam->z += DirectX::XMVectorGetZ(lookTo) * 0.0001f;
//	}
//
//	if (keyboardState.S)
//	{
//		cam->x -= DirectX::XMVectorGetX(lookTo) * 0.0001f;
//		cam->y -= DirectX::XMVectorGetY(lookTo) * 0.0001f;
//		cam->z -= DirectX::XMVectorGetZ(lookTo) * 0.0001f;
//	}
//
//	if (keyboardState.A)
//	{
//		cam->x += DirectX::XMVectorGetX(camRight) * 0.0001f;
//		cam->y += DirectX::XMVectorGetY(camRight) * 0.0001f;
//		cam->z += DirectX::XMVectorGetZ(camRight) * 0.0001f;
//	}
//
//	if (keyboardState.D)
//	{
//		cam->x -= DirectX::XMVectorGetX(camRight) * 0.0001f;
//		cam->y -= DirectX::XMVectorGetY(camRight) * 0.0001f;
//		cam->z -= DirectX::XMVectorGetZ(camRight) * 0.0001f;
//	}
//}

//void GameObject::Move(float deltaTime)
//{
//	auto kbState = InputManager::GetInstance().GetKeyboardState();
//	const float moveSpeed = 10.f * deltaTime;
//
//	if (kbState.W)
//	{
//		m_Transform.pos.z += moveSpeed;
//	}
//
//	if (kbState.S)
//	{
//		m_Transform.pos.z -= moveSpeed;
//	}
//
//	if (kbState.A)
//	{
//		m_Transform.pos.x -= moveSpeed;
//	}
//
//	if (kbState.D)
//	{
//		m_Transform.pos.x += moveSpeed;
//	}
//
//}

GameObject::GameObject(const char* MeshName, const char* MaterialName)
{
	m_ObjectMesh = MeshDatabase::GetInstance().GetMesh(MeshName);
	m_Material   = MaterialDatabase::GetInstance().GetMaterial(MaterialName);
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
}

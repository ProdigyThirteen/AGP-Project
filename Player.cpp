#include "Player.h"
#include "InputManager.h"
#include "Camera.h"

#include <DirectXMath.h>

Player::Player(const char* MeshName, const char* MaterialName, Camera* cam) 
	: GameObject(MeshName, MaterialName),
	  m_Camera(cam)
{

	m_Transform.pos = { 0,0,10 };
	m_Transform.rot = { 0,DirectX::XM_PIDIV2,0 };

	m_Sense = DirectX::XM_2PI * 0.00025f;
	m_Speed = 5.f;
}

Player::~Player()
{
}

void Player::Move(float deltaTime)
{
	auto kbState = InputManager::GetInstance().GetKeyboardState();
	const float moveSpeed = m_Speed * deltaTime;

	auto fv = m_Transform.GetForwardVector();
	auto rv = m_Transform.GetRightVector();

	if (kbState.W)
	{
		m_Transform.pos.x += DirectX::XMVectorGetX(fv) * moveSpeed;
		m_Transform.pos.y += DirectX::XMVectorGetY(fv) * moveSpeed;
		m_Transform.pos.z += DirectX::XMVectorGetZ(fv) * moveSpeed;
	}

	if (kbState.S)
	{
		m_Transform.pos.x -= DirectX::XMVectorGetX(fv) * moveSpeed;
		m_Transform.pos.y -= DirectX::XMVectorGetY(fv) * moveSpeed;
		m_Transform.pos.z -= DirectX::XMVectorGetZ(fv) * moveSpeed;
	}

	if (kbState.A)
	{
		m_Transform.pos.x += DirectX::XMVectorGetX(rv) * moveSpeed;
		m_Transform.pos.y += DirectX::XMVectorGetY(rv) * moveSpeed;
		m_Transform.pos.z += DirectX::XMVectorGetZ(rv) * moveSpeed;
	}

	if (kbState.D)
	{
		m_Transform.pos.x -= DirectX::XMVectorGetX(rv) * moveSpeed;
		m_Transform.pos.y -= DirectX::XMVectorGetY(rv) * moveSpeed;
		m_Transform.pos.z -= DirectX::XMVectorGetZ(rv) * moveSpeed;
	}

	if (kbState.Space)
	{
		m_Transform.pos.y += moveSpeed;
	}

	if (kbState.LeftControl)
	{
		m_Transform.pos.y -= moveSpeed;
	}
}

void Player::Rotate(float deltaTime)
{
	auto mouseState = InputManager::GetInstance().GetMouseState();

	m_Transform.rot.x += mouseState.y * m_Sense;
	m_Transform.rot.y += mouseState.x * m_Sense;
}

void Player::UpdateCamera()
{
	auto fv = m_Transform.GetForwardVector();
	float x = DirectX::XMVectorGetX(fv) * camZOffset;
	float y = DirectX::XMVectorGetY(fv) * camZOffset;
	float z = DirectX::XMVectorGetZ(fv) * camZOffset;

	auto uv = m_Transform.GetUpVector();
	x += DirectX::XMVectorGetX(uv) * camYOffset;
	y += DirectX::XMVectorGetY(uv) * camYOffset;
	z += DirectX::XMVectorGetZ(uv) * camYOffset;

	m_Camera->SetPosition(m_Transform.pos.x + x, 
						  m_Transform.pos.y + y, 
						  m_Transform.pos.z + z);


	m_Camera->SetRotation(m_Transform.rot.x, m_Transform.rot.y, m_Transform.rot.z);
}

void Player::Update(float deltaTime)
{
	Move(deltaTime);
	Rotate(deltaTime);
	UpdateCamera();
}
#include "Player.h"
#include "InputManager.h"
#include "Camera.h"
#include "BoxCollider.h"

#include <DirectXMath.h>
#include "SoundManager.h"

Player::Player(const char* MeshName, const char* MaterialName, Camera* cam) 
	: GameObject(MeshName, MaterialName),
	  m_Camera(cam)
{
	m_Camera->pos = { 0,0,-10 };

	m_Transform.pos = { 0,0,10 };
	m_Transform.rot = { 0,0,0,1 };
	m_Transform.scl = { 0.25f,0.25f,0.25f };

	m_Sense = DirectX::XM_2PI * 0.00025f;
	m_Speed = 25.f;
	m_RotDeg = 3;

	m_Collider = new BoxCollider("Player");
	m_Collider->SetPosition(m_Transform.pos);
	m_Collider->SetRotation(m_Transform.rot);
	m_Collider->SetScale({1,1,1});
	m_Collider->SetOnCollision(std::bind(&Player::OnCollision, this, std::placeholders::_1));

	// Set up listener
	SoundManager::GetInstance().SetListenerPosition(m_Transform.pos);
	SoundManager::GetInstance().SetListenerOrientationFromQuaternion(m_Transform.rot);
}

Player::~Player()
{
	delete m_Collider;
}

void Player::Move(float deltaTime)
{
	auto kbState = InputManager::GetInstance().GetKeyboardState();
	const float speed = m_Speed * deltaTime;

	auto fv = m_Transform.Forward();
	auto rv = m_Transform.Right();

	// Movement
	if (kbState.W)
		m_Transform.pos += fv * speed;
	if (kbState.S)
		m_Transform.pos -= fv * speed;
}

void Player::Rotate(float deltaTime)
{
	auto mouseState = InputManager::GetInstance().GetMouseState();

	float x = mouseState.x;
	float y = mouseState.y;

	// Rotation
	if (x != 0)
		m_Transform.rot *= DirectX::XMQuaternionRotationAxis({ 0,1,0 }, x * m_Sense);

	if (y != 0)
		m_Transform.rot *= DirectX::XMQuaternionRotationAxis(m_Transform.Right(), -y * m_Sense);

}

void Player::PlayDirectionalSound()
{
	// Play sound in direction of pressed arrow key
	auto kbState = InputManager::GetInstance().GetKeyboardTracker();

	// if kb up PRESSED
	if (kbState->pressed.Up)
		SoundManager::GetInstance().PlaySpatialSoundEffect("explosion",{m_Transform.pos.x + 50, m_Transform.pos.y, m_Transform.pos.z + 50},  false);

	if (kbState->pressed.Down)
		SoundManager::GetInstance().PlaySpatialSoundEffect("explosion", {m_Transform.pos.x, m_Transform.pos.y, m_Transform.pos.z - 50}, false);

	if (kbState->pressed.Right)
		SoundManager::GetInstance().PlaySpatialSoundEffect("explosion", {m_Transform.pos.x + 50, m_Transform.pos.y, m_Transform.pos.z}, false);

	if (kbState->pressed.Left)
		SoundManager::GetInstance().PlaySpatialSoundEffect("explosion", {m_Transform.pos.x - 50, m_Transform.pos.y, m_Transform.pos.z}, false);
}

void Player::UpdateCamera()
{
	auto fv = m_Transform.Forward();
	auto uv = m_Transform.Up();

	m_Camera->pos = m_Transform.pos + fv * -10 + uv * 5;
	m_Camera->rot = m_Transform.rot;

}

void Player::OnCollision(BoxCollider* other)
{
	const char* tag = other->GetTag();

	if (tag == "Collectable")
	{
		//OutputDebugStringA("Player collided with Collectable\n");
	}
}

void Player::Update(float deltaTime)
{
	Move(deltaTime);
	Rotate(deltaTime);

	// Debugging
	PlayDirectionalSound();
	
	UpdateCamera();
	m_Transform.rot.Normalize();

	m_Collider->SetPosition(m_Transform.pos);
	m_Collider->SetRotation(m_Transform.rot);

	SoundManager::GetInstance().UpdateListener(m_Transform.pos, m_Transform.rot, deltaTime);
}
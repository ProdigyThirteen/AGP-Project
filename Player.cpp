#include "Player.h"
#include "InputManager.h"
#include "Camera.h"
#include "BoxCollider.h"
#include <DirectXMath.h>
#include "Projectile.h"
#include "SoundManager.h"
#include "Scene.h"

Player::Player(const char* MeshName, const char* MaterialName, Camera* cam, Scene* scene)
    : GameObject(MeshName, MaterialName, scene),
      m_Camera(cam)
{
    // Set up camera
    m_Camera->pos = DirectX::XMVECTOR{0, 0, -10};

    // Set up player
    m_Transform.pos = DirectX::XMVECTOR{0, 0, 10};
    m_Transform.rot = DirectX::XMVECTOR{0, 0, 0, 1};
    m_Transform.scl = DirectX::XMVECTOR{0.5f, 0.5f, 0.5f};

    // Set up player input
    m_Sense = DirectX::XM_2PI * 0.00025f;
    m_Speed = 25.f;
    m_RotDeg = 3;

    // Set up player collider
    m_Collider = new BoxCollider("Player");
    m_Collider->SetPosition(m_Transform.pos);
    m_Collider->SetRotation(m_Transform.rot);
    m_Collider->SetScale({1, 1, 1});
    m_Collider->SetOnCollision(std::bind(&Player::OnCollision, this, std::placeholders::_1));

    // Set up audio listener
    SoundManager::GetInstance().SetListenerPosition(m_Transform.pos);
    SoundManager::GetInstance().SetListenerOrientationFromQuaternion(m_Transform.rot);

    // Set up shooting
    m_RateOfFire = 0.5f;
    m_TimeSinceLastShot = m_RateOfFire;
}

Player::~Player()
{
    delete m_Collider;
    m_Scene->RemoveText(m_PosTextID);
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

    if (x == 0 && y == 0)
        return;

    // Rotation, inverting turn if player upside down
    if (m_Transform.Up().y > 0)
    	m_Transform.rot *= DirectX::XMQuaternionRotationAxis({ 0,1,0 }, x * m_Sense);
    else
        m_Transform.rot *= DirectX::XMQuaternionRotationAxis({ 0,1,0 }, -x * m_Sense);
    
    m_Transform.rot *= DirectX::XMQuaternionRotationAxis(m_Transform.Right(), -y * m_Sense);
}

void Player::Shoot(float deltaTime)
{
    if (m_TimeSinceLastShot < m_RateOfFire)
        m_TimeSinceLastShot += deltaTime;

    auto mouseState = InputManager::GetInstance().GetMouseState();
    if (!mouseState.leftButton)
        return;
    
    if (m_TimeSinceLastShot >= m_RateOfFire)
    {
        m_TimeSinceLastShot = 0;
        // Shoot projectile
        auto projectile = new Projectile("AIM120D", "missile", m_Scene);
        projectile->SetPosition(m_Transform.pos + m_Transform.Forward() * 10);
        projectile->SetRotation(m_Transform.rot);
        projectile->SetScale({0.2f, 0.2f, 0.2f});
        m_Scene->AddGameObject(projectile);

        // Play sfx
        SoundManager::GetInstance().PlaySpatialSoundEffect("shooting", m_Transform.pos, false);
    }
}

void Player::PauseMusic()
{
    auto kbState = InputManager::GetInstance().GetKeyboardTracker();
    if (kbState->pressed.P)
        SoundManager::GetInstance().TogglePause("ambient");
}

void Player::PlayDirectionalSound()
{
    // Play sound in direction of pressed arrow key
    auto kbState = InputManager::GetInstance().GetKeyboardTracker();

    // if kb up PRESSED
    if (kbState->pressed.Up)
        SoundManager::GetInstance().PlaySpatialSoundEffect("explosion", {m_Transform.pos.x + 50, m_Transform.pos.y, m_Transform.pos.z + 50}, false);

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
}

void Player::Update(float deltaTime)
{
    Move(deltaTime);
    Rotate(deltaTime);
    Shoot(deltaTime);
    PauseMusic();

    // Debugging
    PlayDirectionalSound();

    UpdateCamera();
    m_Transform.rot.Normalize();

    m_Collider->SetPosition(m_Transform.pos);
    m_Collider->SetRotation(m_Transform.rot);

    SoundManager::GetInstance().UpdateListener(m_Transform.pos, m_Transform.rot, deltaTime);
}

#include "Collectable.h"

#include <iostream>

#include "BoxCollider.h"
#include "SoundManager.h"

void Collectable::OnCollision(BoxCollider* other)
{
    // If the player collides with the collectable, destroy it
    if (other->GetTag() == "Player" && !IsMarkedForDestruction())
    {
        Destroy();
        SoundManager::GetInstance().PlaySpatialSoundEffect("explosion", m_Transform.pos, false);
        //SoundManager::GetInstance().PlaySoundEffect("explosion");
    }
}

Collectable::Collectable(const char* MeshName, const char* MaterialName)
    : GameObject(MeshName, MaterialName)
{
    m_Collider = new BoxCollider("Collectable");
    m_Collider->SetTransform(m_Transform);
    m_Collider->SetOnCollision(std::bind(&Collectable::OnCollision, this, std::placeholders::_1));

    // Set random rotation
    m_Transform.rot = DirectX::XMQuaternionRotationAxis({1, 1, 1}, (float)rand() / RAND_MAX * DirectX::XM_2PI);

    // Set random bob height
    bob = (float)rand() / RAND_MAX * DirectX::XM_2PI;

    // Set random position
    m_Transform.pos = {(float)rand() / RAND_MAX * 500 - 200, (float)rand() / RAND_MAX * 500 - 200, (float)rand() / RAND_MAX * 500 - 200};
    m_Transform.scl = {3, 3, 3};

    m_StartY = m_Transform.pos.y;
}

Collectable::~Collectable()
{
    delete m_Collider;
    m_Collider = nullptr;
}

void Collectable::Update(float deltaTime)
{
    // Update collider to match transform
    m_Collider->SetTransform(m_Transform);

    // Spin
    m_Transform.rot *= DirectX::XMQuaternionRotationAxis({0, 1, 0}, m_RotationSpeed * deltaTime);

    // Move up and down
    bob += m_BobSpeed * deltaTime;
    m_Transform.pos.y = m_StartY + sin(bob) * 2;
}

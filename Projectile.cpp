#include "Projectile.h"
#include "BoxCollider.h"
#include "MaterialDatabase.h"
#include "Scene.h"
#include "SoundManager.h"

void Projectile::OnCollision(BoxCollider* other)
{
    if (other->GetTag() == "Collectable")
    {
        Destroy();
        SoundManager::GetInstance().PlaySpatialSoundEffect("explosion", m_Transform.pos, false);
    }
}

Projectile::Projectile(const char* MeshName, const char* MaterialName, Scene* scene)
    : GameObject(MeshName, MaterialName, scene)
{
    m_Collider = new BoxCollider("Missile");
    m_Collider->SetPosition(m_Transform.pos);
    m_Collider->SetRotation(m_Transform.rot);
    m_Collider->SetScale({1,1,1}); // Missile scale is tiny, so we need to scale the collider up
    m_Collider->SetOnCollision(std::bind(&Projectile::OnCollision, this, std::placeholders::_1));

    m_Speed = 100.0f;
    m_Lifespan = 2.0f;
}

Projectile::~Projectile()
{
    delete m_Collider;
}

void Projectile::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    m_Collider->SetPosition(m_Transform.pos);
    m_Collider->SetRotation(m_Transform.rot);

    m_TimeAlive += deltaTime;
    if (m_TimeAlive >= m_Lifespan && !IsMarkedForDestruction()) // If lifespan is over, destroy, but only if not already marked for destruction
        Destroy();
    else if (IsMarkedForDestruction()) // If marked for destruction, don't do anything else
        return;

    // Move forward
    m_Transform.Translate(m_Transform.Forward() * m_Speed * deltaTime);
}


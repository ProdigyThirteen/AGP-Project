#pragma once
#include "GameObject.h"

class BoxCollider;

class Projectile : public GameObject
{
private:
    BoxCollider* m_Collider = nullptr;
    float m_Speed = 0.0f;
    float m_Lifespan = 0.0f;
    float m_TimeAlive = 0.0f;

    void OnCollision(BoxCollider* other);
    
public:
    Projectile(const char* MeshName, const char* MaterialName, Scene* scene);
    ~Projectile();

    void Update(float deltaTime) override;
};

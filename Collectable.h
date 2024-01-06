#pragma once

#include "GameObject.h"

class BoxCollider;

class Collectable : public GameObject
{
private:
	BoxCollider* m_Collider = nullptr;

	void OnCollision(BoxCollider* other);

	// For bobbing
	const float m_RotationSpeed = 2.f;
	const float m_BobSpeed = 2.f;
	float m_StartY = 0;
	float bob = 0.0f;

public:
	Collectable(const char* MeshName, const char* MaterialName);
	~Collectable();

	void Update(float deltaTime);
};


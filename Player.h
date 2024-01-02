#pragma once

#include "GameObject.h"
class Camera;

class Player : public GameObject
{
private:
	const float camZOffset = -5.0f;
	const float camYOffset = -2.0f;

	float m_Speed = 0.0f;
	float m_Sense = 0.0f;

	void Move(float deltaTime);
	void Rotate(float deltaTime);

	Camera* m_Camera = nullptr;
	void UpdateCamera();

public:
	Player(const char* MeshName, const char* MaterialName, Camera* cam);
	~Player();

	void Update(float deltaTime);

	void SetSpeed(float speed) { m_Speed = speed; }
	void SetSense(float sense) { m_Sense = sense; }
};


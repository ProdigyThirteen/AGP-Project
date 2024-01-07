#pragma once
#include "GameObject.h"
struct Camera;
class BoxCollider;

class Player : public GameObject
{
private:
	BoxCollider* m_Collider = nullptr;

	float m_Speed = 0.0f;
	float m_RotDeg = 0.0f;
	float m_Sense = 0.0f;

	float m_RateOfFire = 0.0f;
	float m_TimeSinceLastShot = 0.0f;
	int m_PosTextID;

	void Move(float deltaTime);
	void Rotate(float deltaTime);
	void Shoot(float deltaTime);
	void PauseMusic(); // So you can hear the spatial sound effects

	// For debugging
	void PlayDirectionalSound();

	Camera* m_Camera = nullptr;
	const float camYOffset = 5.f;
	void UpdateCamera();

	void OnCollision(BoxCollider* other);

public:
	Player(const char* MeshName, const char* MaterialName, Camera* cam, Scene* scene);
	~Player();

	void Update(float deltaTime);

	void SetSpeed(float speed) { m_Speed = speed; }
	void SetSense(float sense) { m_Sense = sense; }
};


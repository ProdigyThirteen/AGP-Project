#pragma once

#include <vector>

// Forward declaration
class BoxCollider;


class CollisionManager
{
private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager& other) = delete;
	CollisionManager(CollisionManager&& other) noexcept = delete;
	CollisionManager& operator=(const CollisionManager& other) = delete;

	static std::vector<BoxCollider*> m_Colliders;

public:
	~CollisionManager() = default;

	static CollisionManager& GetInstance()
	{
		static CollisionManager instance;
		return instance;
	}

	static void AddCollider(BoxCollider* collider);
	static void RemoveCollider(BoxCollider* collider);

	static void CheckCollisions();

	static void Clear();
};


#include "CollisionManager.h"
#include "BoxCollider.h"

std::vector<BoxCollider*> CollisionManager::m_Colliders;

void CollisionManager::AddCollider(BoxCollider* collider)
{
	OutputDebugString(L"Adding collider\n");
	m_Colliders.push_back(collider);
}

void CollisionManager::RemoveCollider(BoxCollider* collider)
{
	OutputDebugString(L"Removing collider\n");
	auto it = std::find(m_Colliders.begin(), m_Colliders.end(), collider);
	if (it != m_Colliders.end())
		m_Colliders.erase(it);
}

void CollisionManager::CheckCollisions()
{
	for (auto it = m_Colliders.begin(); it != m_Colliders.end(); ++it)
	{
		for (auto it2 = it + 1; it2 != m_Colliders.end(); ++it2)
		{
			if ((*it)->IsColliding(*it2))
			{
				(*it)->OnCollision(*it2);
				(*it2)->OnCollision(*it);
			}
		}
	}
}

void CollisionManager::Clear()
{
	for (size_t i = 0; i < m_Colliders.size(); ++i)
	{
		delete m_Colliders[i];
	}

	m_Colliders.clear();
}

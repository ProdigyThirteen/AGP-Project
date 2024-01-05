#include "BoxCollider.h"
#include "CollisionManager.h"

BoxCollider::BoxCollider()
{
	CollisionManager::GetInstance().AddCollider(this);
}

BoxCollider::BoxCollider(const char* tag)
{
	m_Tag = tag;
	CollisionManager::GetInstance().AddCollider(this);
}

BoxCollider::~BoxCollider()
{
	CollisionManager::GetInstance().RemoveCollider(this);
}

bool BoxCollider::IsColliding(BoxCollider* other)
{
	auto& t1 = m_Transform;
	auto& t2 = other->m_Transform;

	auto t1Min = t1.pos - t1.scl;
	auto t1Max = t1.pos + t1.scl;

	auto t2Min = t2.pos - t2.scl;
	auto t2Max = t2.pos + t2.scl;

	if (t1Min.x > t2Max.x || t1Max.x < t2Min.x)
		return false;

	if (t1Min.y > t2Max.y || t1Max.y < t2Min.y)
		return false;

	if (t1Min.z > t2Max.z || t1Max.z < t2Min.z)
		return false;

	return true;
}

void BoxCollider::OnCollision(BoxCollider* other)
{
	if (m_OnCollision)
		m_OnCollision(other);
}

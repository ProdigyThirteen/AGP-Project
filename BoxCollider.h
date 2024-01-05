#pragma once

#include "Transform.h"
#include <functional>

class BoxCollider
{
private:
	std::function<void(BoxCollider*)> m_OnCollision;
	Transform m_Transform;
	const char* m_Tag = "";

public:
	BoxCollider();
	BoxCollider(const char* tag);
	virtual ~BoxCollider();

	bool IsColliding(BoxCollider* other);
	void OnCollision(BoxCollider* other);


	// Getters and setters
	void SetOnCollision(std::function<void(BoxCollider*)> func) { m_OnCollision = func; }

	Transform& GetTransform() { return m_Transform; }
	void SetTransform(const Transform& transform) { m_Transform = transform; }

	DirectX::SimpleMath::Vector3 GetPosition() { return m_Transform.pos; }
	void SetPosition(const DirectX::SimpleMath::Vector3& pos) { m_Transform.pos = pos; }

	DirectX::SimpleMath::Vector3 GetScale() { return m_Transform.scl; }
	void SetScale(const DirectX::SimpleMath::Vector3& scl) { m_Transform.scl = scl; }

	DirectX::SimpleMath::Quaternion GetRotation() { return m_Transform.rot; }
	void SetRotation(const DirectX::SimpleMath::Quaternion& rot) { m_Transform.rot = rot; }

	const char* GetTag() { return m_Tag; }
};


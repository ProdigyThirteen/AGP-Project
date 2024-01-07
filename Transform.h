#pragma once
#include <SimpleMath.h>

struct Transform
{
	DirectX::SimpleMath::Vector3	pos = { 0, 0, 0 };
	DirectX::SimpleMath::Quaternion rot = { 0, 0, 0, 1 };
	DirectX::SimpleMath::Vector3	scl = { 1, 1, 1 };

	DirectX::XMMATRIX GetWorldMatrix()
	{
		DirectX::XMMATRIX translation = DirectX::XMMatrixTranslationFromVector(pos);
		DirectX::XMMATRIX rotation =	DirectX::XMMatrixRotationQuaternion(rot);
		DirectX::XMMATRIX scaling =		DirectX::XMMatrixScalingFromVector(scl);

		return scaling * rotation * translation;
	}

    // Get the forward vector
    DirectX::SimpleMath::Vector3 Forward() const
    {
        return DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Forward, rot);
    }

    // Get the right vector
    DirectX::SimpleMath::Vector3 Right() const
    {
        return DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Right, rot);
    }

    // Get the up vector
    DirectX::SimpleMath::Vector3 Up() const
    {
        return DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Up, rot);
    }

	void Translate(const DirectX::SimpleMath::Vector3& translation)
	{
		pos += translation;
	}
};
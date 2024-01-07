#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

struct Camera
{
	using Vector3 = DirectX::SimpleMath::Vector3;
	using Quaternion = DirectX::SimpleMath::Quaternion;
	
	Vector3 pos = { 0, 0, -5 };
	Quaternion rot = { 0, 0, 0, 1 };

	DirectX::XMMATRIX GetViewMatrix()
	{
		Vector3 forward = Forward();
		Vector3 up = Up();

		return DirectX::XMMatrixLookToLH(pos, forward, up);
	}

	DirectX::SimpleMath::Vector3 Forward()
	{
		return Vector3::Transform(Vector3::Forward, rot);
	}

	DirectX::SimpleMath::Vector3 Right()
	{
		return Vector3::Transform(Vector3::Right, rot);
	}

	DirectX::SimpleMath::Vector3 Up()
	{
		return Vector3::Transform(Vector3::Up, rot);
	}
};
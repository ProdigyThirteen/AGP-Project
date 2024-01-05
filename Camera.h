#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

struct Camera
{
	DirectX::SimpleMath::Vector3 pos = { 0, 0, -5 };
	DirectX::SimpleMath::Quaternion rot = { 0, 0, 0, 1 };

	DirectX::XMMATRIX GetViewMatrix()
	{
		DirectX::SimpleMath::Vector3 forward = Forward();
		DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3::Up;

		return DirectX::XMMatrixLookToLH(pos, forward, up);
	}

	DirectX::SimpleMath::Vector3 Forward()
	{
		return DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Forward, rot);
	}

	DirectX::SimpleMath::Vector3 Right()
	{
		return { sin(rot.y - DirectX::XM_PIDIV2), 0, cos(rot.y - DirectX::XM_PIDIV2) };
	}

	DirectX::SimpleMath::Vector3 Up()
	{
		return DirectX::SimpleMath::Vector3::Up * rot;
	}
};
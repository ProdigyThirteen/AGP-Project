#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

struct Camera
{
	float x = 0, y = 0, z = 0;
	float pitch = DirectX::XM_PIDIV2, yaw = 0, roll = 0;

	DirectX::XMMATRIX GetViewMatrix()
	{
		DirectX::XMVECTOR eyePos{ x, y, z };
		DirectX::XMVECTOR camUp{ 0, 1, 0 };

		if (pitch == 0 && yaw == 0)
		{
			pitch = 0.0001f;
			yaw = 0.0001f;
		}

		DirectX::XMVECTOR lookTo{ sin(yaw)* sin(pitch),
			cos(pitch),
			cos(yaw)* sin(pitch) };
		DirectX::XMMATRIX view = DirectX::XMMatrixLookToLH(eyePos, lookTo, camUp);
		return view;
	}

	void SetPosition(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void SetRotation(float pitch, float yaw, float roll)
	{
		this->pitch = pitch;
		this->yaw = yaw;
		this->roll = roll;
	}
};
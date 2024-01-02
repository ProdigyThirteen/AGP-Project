#pragma once
#include <DirectXMath.h>

struct Transform
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 rot;
	DirectX::XMFLOAT3 scl;

	DirectX::XMMATRIX GetWorldMaxtrix()
	{
		const DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
		const DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
		const DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(scl.x, scl.y, scl.z);
		const DirectX::XMMATRIX world = scale * rotation * translation;
		return world;
	}

	// Forward vector
	DirectX::XMVECTOR GetForwardVector()
	{
		const DirectX::XMVECTOR lookTo = DirectX::XMVector3Normalize(DirectX::XMVectorSet(sin(rot.y) * sin(rot.x),
										 cos(rot.x),
										 cos(rot.y) * sin(rot.x), 0));
		return lookTo;
	}

	// Right vector
	DirectX::XMVECTOR GetRightVector()
	{
		const DirectX::XMVECTOR right = DirectX::XMVector3Cross(GetForwardVector(), DirectX::XMVectorSet(0, 1, 0, 0));
		return right;
	}

	// Up vector
	DirectX::XMVECTOR GetUpVector()
	{
		const DirectX::XMVECTOR lookTo = DirectX::XMVector3Normalize(DirectX::XMVectorSet(sin(rot.y) * sin(rot.x + DirectX::XM_PIDIV2),
										 cos(rot.x + DirectX::XM_PIDIV2),
										 cos(rot.y) * sin(rot.x + DirectX::XM_PIDIV2), 0));
		return lookTo;
	}
};
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
};
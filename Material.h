#pragma once

#include <d3d11.h>
#include "ShaderData.h"

struct Material
{
	ID3D11ShaderResourceView* Texture;
	ShaderData* Shader;

	Material()
	{
		Texture = nullptr;
		Shader = nullptr;
	}

	Material(ID3D11ShaderResourceView* texture, ShaderData* shader)
	{
		Texture = texture;
		Shader = shader;
	}

	~Material() = default;
};
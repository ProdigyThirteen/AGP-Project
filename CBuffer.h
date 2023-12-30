#pragma once
#include <directxmath.h>
#include "PointLight.h"
#include "Globals.h"

struct CBUFFER0
{
	DirectX::XMMATRIX WVP;
	//DirectX::XMMATRIX WV;
	DirectX::XMVECTOR ambientLightColour;
	DirectX::XMVECTOR directionalLightDir;
	DirectX::XMVECTOR directionalLightCol;

	PointLight pointLights[MAX_POINT_LIGHTS];
};
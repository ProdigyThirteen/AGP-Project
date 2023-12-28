#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

// Forward declarations
class ObjFileModel;
struct Material;
struct Camera;

struct SkyboxCBuffer
{
	DirectX::XMMATRIX WVP;
};

class Skybox
{
private:
	ID3D11RasterizerState*    pRasterSolid		= nullptr;
	ID3D11RasterizerState*    pRasterSkybox		= nullptr;
	ID3D11DepthStencilState*  pDepthWriteSolid	= nullptr;
	ID3D11DepthStencilState*  pDepthWriteSkybox = nullptr;
	ID3D11Buffer*			  pSkyboxCBuffer	= nullptr;
	ID3D11SamplerState*		  pSkyboxSampler	= nullptr;
	
	Material*				  pSkyboxMaterial	= nullptr;
	ObjFileModel*			  pSkyboxMesh		= nullptr;

public:
	Skybox() = default;
	~Skybox()
	{
		if (pRasterSolid)		pRasterSolid->Release();
		if (pRasterSkybox)		pRasterSkybox->Release();
		if (pDepthWriteSolid)	pDepthWriteSolid->Release();
		if (pDepthWriteSkybox)	pDepthWriteSkybox->Release();
		if (pSkyboxCBuffer)		pSkyboxCBuffer->Release();
		if (pSkyboxSampler)		pSkyboxSampler->Release();
	};

	HRESULT Init(ID3D11Device* Device);
	void Draw(ID3D11DeviceContext* DeviceContext, Camera* cam);

};


#include "Skybox.h"
#include "MeshDatabase.h"
#include "MaterialDatabase.h"
#include "Material.h"
#include "Globals.h"
#include "Camera.h"


HRESULT Skybox::Init(ID3D11Device* Device)
{
    // Set skybox mesh
    pSkyboxMesh = MeshDatabase::GetInstance().GetMesh("cube");
	if (!pSkyboxMesh)
	{
		OutputDebugString(L"Failed to get skybox mesh\n");
		return E_FAIL;
	}
	OutputDebugString(L"Got skybox mesh\n");

    // Set skybox material
    pSkyboxMaterial = MaterialDatabase::GetInstance().GetMaterial("skybox");
	if (!pSkyboxMaterial)
	{
		OutputDebugString(L"Failed to get skybox material\n");
		return E_FAIL;
	}
	OutputDebugString(L"Got skybox material\n");


	HRESULT result;

    // Setup skybox rasterizer states
    D3D11_RASTERIZER_DESC rasterDesc;
    ZeroMemory(&rasterDesc, sizeof(rasterDesc));
    rasterDesc.CullMode = D3D11_CULL_BACK;
    rasterDesc.FillMode = D3D11_FILL_SOLID;
    result = Device->CreateRasterizerState(&rasterDesc, &pRasterSolid);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to create solid rasterizer state\n");
		return result;
	}

    rasterDesc.CullMode = D3D11_CULL_FRONT;
    result = Device->CreateRasterizerState(&rasterDesc, &pRasterSkybox);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to create skybox rasterizer state\n");
		return result;
	}

	OutputDebugString(L"Created rasterizer states\n");

    D3D11_DEPTH_STENCIL_DESC depthDesc = { 0 };
    depthDesc.DepthEnable = true;
    depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthDesc.DepthFunc = D3D11_COMPARISON_LESS;
    result = Device->CreateDepthStencilState(&depthDesc, &pDepthWriteSolid);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to create solid depth stencil state\n");
		return result;
	}

    depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
    result = Device->CreateDepthStencilState(&depthDesc, &pDepthWriteSkybox);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to create skybox depth stencil state\n");
		return result;
	}

	OutputDebugString(L"Created skybox depth stencil states\n");

	// Setup skybox sampler state
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	result = Device->CreateSamplerState(&sampDesc, &pSkyboxSampler);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to create skybox sampler state\n");
		return result;
	}

	OutputDebugString(L"Created skybox sampler state\n");

	// Setup skybox constant buffer
	D3D11_BUFFER_DESC cBufferDesc = { 0 };
	cBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	cBufferDesc.ByteWidth = sizeof(SkyboxCBuffer);
	cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	result = Device->CreateBuffer(&cBufferDesc, NULL, &pSkyboxCBuffer);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to create skybox constant buffer\n");
		return result;
	}

	OutputDebugString(L"Created skybox constant buffer\n");

    return S_OK;
}

void Skybox::Draw(ID3D11DeviceContext* DeviceContext, Camera* cam)
{
	// Front-face culling and disable depth writing
	DeviceContext->OMSetDepthStencilState(pDepthWriteSkybox, 1);
	DeviceContext->RSSetState(pRasterSkybox);

	// Set skybox shaders
	DeviceContext->IASetInputLayout(pSkyboxMaterial->Shader->InputLayout);
	DeviceContext->VSSetShader(pSkyboxMaterial->Shader->VertexShader, 0, 0);
	DeviceContext->PSSetShader(pSkyboxMaterial->Shader->PixelShader, 0, 0);

	// Constant buffer data
	SkyboxCBuffer cBuffer = { DirectX::XMMATRIX() };
	DirectX::XMMATRIX translation, projection, view;
	translation = DirectX::XMMatrixTranslationFromVector(cam->pos);
	projection  = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

	view = cam->GetViewMatrix();
	cBuffer.WVP = translation * view * projection;
	DeviceContext->UpdateSubresource(pSkyboxCBuffer, 0, 0, &cBuffer, 0, 0);

	// Set shader resources
	DeviceContext->VSSetConstantBuffers(0, 1, &pSkyboxCBuffer);
	DeviceContext->PSSetSamplers(0, 1, &pSkyboxSampler);
	DeviceContext->PSSetShaderResources(0, 1, &pSkyboxMaterial->Texture);

	pSkyboxMesh->Draw();

	// Reset depth writing and culling
	DeviceContext->OMSetDepthStencilState(pDepthWriteSolid, 1);
	DeviceContext->RSSetState(pRasterSolid);

	// Reset shaders
	Material* pMaterial = MaterialDatabase::GetInstance().GetMaterial("default");
	DeviceContext->VSSetShader(pMaterial->Shader->VertexShader, 0, 0);
	DeviceContext->PSSetShader(pMaterial->Shader->PixelShader, 0, 0);
	DeviceContext->IASetInputLayout(pMaterial->Shader->InputLayout);
}

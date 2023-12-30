#include "Renderer.h"
#include "Globals.h"

#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include "CBuffer.h"

#include "Scene.h"
#include "Skybox.h"
#include "GameObject.h"
#include "Camera.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
	if (m_DeviceContext) m_DeviceContext->Release();
	if (m_SamplerState) m_SamplerState->Release();
	if (m_BackBuffer) m_BackBuffer->Release();
	if (m_SwapChain) m_SwapChain->Release();
	if (m_ZBuffer) m_ZBuffer->Release();
	if (m_CBuffer) m_CBuffer->Release();
	if (m_Device) m_Device->Release();

}

HRESULT Renderer::Init(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC scd = {};
	// Set up the swap chain description
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Width = SCREEN_WIDTH;
	scd.BufferDesc.Height = SCREEN_HEIGHT;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 1;
	scd.Windowed = TRUE;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// Create the device and swap chain
	HRESULT hr;
	hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&m_SwapChain,
		&m_Device,
		NULL,
		&m_DeviceContext);

	if (FAILED(hr))
	{
		OutputDebugStringA("Failed to create device and swap chain");
		return hr;
	}

	// Setup back buffer
	ID3D11Texture2D* pBackBufferTexture = nullptr;
	hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBufferTexture);
	if (FAILED(hr))
	{
		OutputDebugStringA("Failed to get back buffer");
		return hr;
	}

	hr = m_Device->CreateRenderTargetView(pBackBufferTexture, NULL, &m_BackBuffer);
	if (FAILED(hr))
	{
		OutputDebugStringA("Failed to create render target view");
		return hr;
	}

	pBackBufferTexture->Release();

	// Set render target
	D3D11_TEXTURE2D_DESC tex2dDesc = { 0 };
	tex2dDesc.Width = SCREEN_WIDTH;
	tex2dDesc.Height = SCREEN_HEIGHT;
	tex2dDesc.ArraySize = 1;
	tex2dDesc.MipLevels = 1;
	tex2dDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tex2dDesc.SampleDesc.Count = scd.SampleDesc.Count;
	tex2dDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tex2dDesc.Usage = D3D11_USAGE_DEFAULT;

	// Create Z buffer
	ID3D11Texture2D* pZBufferTexture = nullptr;
	hr = m_Device->CreateTexture2D(&tex2dDesc, NULL, &pZBufferTexture);
	if (FAILED(hr))
	{
		OutputDebugStringA("Failed to create Z buffer texture");
		return E_FAIL;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	dsvd.Format = tex2dDesc.Format;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	hr = m_Device->CreateDepthStencilView(pZBufferTexture, &dsvd, &m_ZBuffer);
	if (FAILED(hr))
	{
		OutputDebugString(L"Failed to create Z buffer");
		return E_FAIL;
	}
	pZBufferTexture->Release();

	m_DeviceContext->OMSetRenderTargets(1, &m_BackBuffer, m_ZBuffer);

	// Setup viewport
	D3D11_VIEWPORT vp = {};
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = SCREEN_WIDTH;
	vp.Height = SCREEN_HEIGHT;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	m_DeviceContext->RSSetViewports(1, &vp);

	// Set topology
	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Set constant buffer
	D3D11_BUFFER_DESC cb = { 0 };
	cb.Usage = D3D11_USAGE_DEFAULT;
	cb.ByteWidth = sizeof(CBUFFER0);
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hr = m_Device->CreateBuffer(&cb, NULL, &m_CBuffer);
	if(FAILED(hr))
	{
		OutputDebugString(L"Failed to create constant buffer");
		return E_FAIL;
	}
	OutputDebugString(L"Successfully created constant buffer\n");

	// Set sampler state
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	m_Device->CreateSamplerState(&sampDesc, &m_SamplerState);

	return S_OK;
}

void Renderer::DrawFrame(Scene* scene)
{
	m_DeviceContext->ClearRenderTargetView(m_BackBuffer, DirectX::Colors::DarkSlateBlue);
	m_DeviceContext->ClearDepthStencilView(m_ZBuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);

	// Draw skybox
	scene->GetSkybox()->Draw(m_DeviceContext, scene->GetCamera());

	// Setting up data for drawing objects
	DirectX::XMMATRIX w, v, p;
	v = scene->GetCamera()->GetViewMatrix();
	p = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

	CBUFFER0 cBuffer;
	Material* material;

	// Set sampler state
	m_DeviceContext->PSSetSamplers(0, 1, &m_SamplerState);

	for (auto& gameObject : scene->GetGameObjects())
	{
		material = gameObject->GetMaterial();

		// Set world matrix
		w = gameObject->GetTransform().GetWorldMaxtrix();

		// Set material
		m_DeviceContext->PSSetShaderResources(0, 1, &material->Texture);

		// Set shaders
		m_DeviceContext->IASetInputLayout(material->Shader->InputLayout);
		m_DeviceContext->VSSetShader(material->Shader->VertexShader, 0, 0);
		m_DeviceContext->PSSetShader(material->Shader->PixelShader, 0, 0);

		// Set up constant buffer
		cBuffer.WVP = w * v * p ;
		//cBuffer.WV  = w * v;

		cBuffer.ambientLightColour = { 0.5f, 0.5f, 0.5f, 1.0f };
		cBuffer.directionalLightCol = { 0.0f, 0.0f, 0.0f, 0.0f };
		cBuffer.directionalLightDir = { 0.0f, 0.0f, 0.0f, 0.0f };

		// Update constant buffer
		m_DeviceContext->UpdateSubresource(m_CBuffer, 0, NULL, &cBuffer, 0, 0);
		m_DeviceContext->VSSetConstantBuffers(0, 1, &m_CBuffer);

		// Draw mesh
		gameObject->GetMesh()->Draw();
	}


	m_SwapChain->Present(0, 0);
}
#include "Renderer.h"
#include "Globals.h"

#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	if (m_DeviceContext)
	{
		m_DeviceContext->ClearState();
		m_DeviceContext->Release();
	}

	if (m_Device)
	{
		m_Device->Release();
	}

	if (m_SwapChain)
	{
		m_SwapChain->Release();
	}

	if (m_BackBuffer)
	{
		m_BackBuffer->Release();
	}

	if (m_ZBuffer)
	{
		m_ZBuffer->Release();
	}
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

	return S_OK;
}

void Renderer::DrawFrame()
{
	m_DeviceContext->ClearRenderTargetView(m_BackBuffer, DirectX::Colors::DarkSlateBlue);
	m_DeviceContext->ClearDepthStencilView(m_ZBuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);

	m_SwapChain->Present(0, 0);
}

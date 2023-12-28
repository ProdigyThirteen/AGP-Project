#pragma once
#include <d3d11.h>
#include <DirectXMath.h>


class Renderer
{
private:
	IDXGISwapChain* m_SwapChain;
	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_DeviceContext;
	ID3D11RenderTargetView* m_BackBuffer;
	ID3D11DepthStencilView* m_ZBuffer;

public:
	Renderer();
	~Renderer();

	HRESULT Init(HWND hWnd);
	void DrawFrame();

	ID3D11Device* GetDevice() { return m_Device; }
	ID3D11DeviceContext* GetDeviceContext() { return m_DeviceContext; }
};


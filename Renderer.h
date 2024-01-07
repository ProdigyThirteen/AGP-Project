#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "ShaderManager.h"
#include <SpriteFont.h>

// Forward declarations
class Scene;

class Renderer
{
private:
	IDXGISwapChain*			  m_SwapChain	  = nullptr;
	ID3D11Device*			  m_Device		  = nullptr;
	ID3D11DeviceContext*	  m_DeviceContext = nullptr;
	ID3D11RenderTargetView*   m_BackBuffer	  = nullptr;
	ID3D11DepthStencilView*   m_ZBuffer		  = nullptr;

	ID3D11SamplerState*		  m_SamplerState  = nullptr;
	ID3D11ShaderResourceView* m_TargetTexture = nullptr;
	ID3D11ShaderResourceView* m_SkyboxTexture = nullptr;

	ID3D11Buffer*			  m_IBuffer		  = nullptr;
	ID3D11Buffer*			  m_CBuffer		  = nullptr;

	// Text rendering
	std::unique_ptr<DirectX::SpriteBatch> m_SpriteBatch;
	std::unique_ptr<DirectX::SpriteFont> m_SpriteFont;

	// Blend state
	ID3D11BlendState* pAlphaBlendStateEnable = nullptr;
	ID3D11BlendState* pAlphaBlendStateDisable = nullptr;


	ShaderManager* m_ShaderManager = nullptr;
public:
	Renderer();
	~Renderer();

	HRESULT Init(HWND hWnd);
	void DrawFrame(Scene* scene);

	ID3D11Device* GetDevice() { return m_Device; }
	ID3D11DeviceContext* GetDeviceContext() { return m_DeviceContext; }
};


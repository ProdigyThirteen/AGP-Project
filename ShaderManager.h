#pragma once
#include <d3d11.h>
#include <map>
#include <string>

// Forward declarations
struct ShaderData;

class ShaderManager
{
private:
	ShaderManager() = default;
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator=(const ShaderManager&) = delete;

	std::map<std::string, ShaderData*> m_shaders;

	HRESULT LoadVertexShader(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, LPCWSTR fileName, LPCSTR entrypoint, ShaderData& shader);
	HRESULT LoadPixelShader(ID3D11Device* Device, LPCWSTR fileName, LPCSTR entrypoint, ShaderData& shader);

	HRESULT LoadCompiledVertexShader(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, LPCWSTR fileName, ShaderData* shader);
	HRESULT LoadCompiledPixelShader(ID3D11Device* Device, LPCWSTR fileName, ShaderData* shader);

public:
	~ShaderManager() = default;

	static ShaderManager& GetInstance()
	{
		static ShaderManager instance; 
		return instance;
	}

	HRESULT CreateShaders(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext);

	ShaderData* GetShader(const std::string& shaderName);

	void ReleaseShaders();
};


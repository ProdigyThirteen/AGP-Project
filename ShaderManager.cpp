#include "ShaderManager.h"

#include <d3dcompiler.h>
#include "ReadData.h"
#include "ShaderData.h"

HRESULT ShaderManager::LoadVertexShader(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, LPCWSTR fileName, LPCSTR entrypoint, ShaderData& shader)
{
	HRESULT result;
	ID3DBlob* VSblob, * errorBlob;

	result = D3DCompileFromFile(fileName, NULL, NULL, entrypoint, "vs_4_0", NULL, NULL, &VSblob, &errorBlob);
	if (FAILED(result))
	{
		OutputDebugStringA(reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
		errorBlob->Release();
		return result;
	}

	result = Device->CreateVertexShader(VSblob->GetBufferPointer(), VSblob->GetBufferSize(), NULL, &shader.VertexShader);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to create vertex shader\n");
		return result;
	}

	ID3D11ShaderReflection* vShaderReflection = nullptr;
	result = D3DReflect(VSblob->GetBufferPointer(), VSblob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&vShaderReflection);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to reflect vertex shader\n");
		return result;
	}

	D3D11_SHADER_DESC shaderDesc;
	result = vShaderReflection->GetDesc(&shaderDesc);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to get vertex shader description\n");
		return result;
	}

	auto paramDesc = new D3D11_SIGNATURE_PARAMETER_DESC[shaderDesc.InputParameters]{ 0 };
	for (UINT i = 0; i < shaderDesc.InputParameters; i++)
	{
		result = vShaderReflection->GetInputParameterDesc(i, &paramDesc[i]);
		if (FAILED(result))
		{
			OutputDebugString(L"Failed to get vertex shader input parameter description\n");
			return result;
		}
	}

	auto ied = new D3D11_INPUT_ELEMENT_DESC[shaderDesc.InputParameters]{ 0 };
	for (size_t i = 0; i < shaderDesc.InputParameters; i++)
	{
		ied[i].SemanticName = paramDesc[i].SemanticName;
		ied[i].SemanticIndex = paramDesc[i].SemanticIndex;

		if (paramDesc[i].ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
		{
			switch (paramDesc[i].Mask)
			{
			case 1:
				ied[i].Format = DXGI_FORMAT_R32_FLOAT;
				break;

			case 3:
				ied[i].Format = DXGI_FORMAT_R32G32_FLOAT;
				break;

			case 7:
				ied[i].Format = DXGI_FORMAT_R32G32B32_FLOAT;
				break;

			case 15:
				ied[i].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
				break;

			default:
				break;
			}
		}

		ied[i].InputSlot = 0;
		ied[i].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		ied[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		ied[i].InstanceDataStepRate = 0;

	}


	result = Device->CreateInputLayout(ied, shaderDesc.InputParameters, VSblob->GetBufferPointer(), VSblob->GetBufferSize(), &shader.InputLayout);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to create input layout\n");
		return result;
	}
	OutputDebugString(L"Successfully created input layout\n");

	DeviceContext->IASetInputLayout(shader.InputLayout);

	delete[] paramDesc;
	delete[] ied;

	return S_OK;
}

HRESULT ShaderManager::LoadPixelShader(ID3D11Device* Device, LPCWSTR fileName, LPCSTR entrypoint, ShaderData& shader)
{
	HRESULT result;
	ID3DBlob* PSblob, * errorBlob;

	result = D3DCompileFromFile(fileName, NULL, NULL, entrypoint, "ps_4_0", NULL, NULL, &PSblob, &errorBlob);
	if (FAILED(result))
	{
		OutputDebugStringA(reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
		errorBlob->Release();
		return result;
	}

	result = Device->CreatePixelShader(PSblob->GetBufferPointer(), PSblob->GetBufferSize(), NULL, &shader.PixelShader);
	PSblob->Release();
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to create pixel shader\n");
		return result;
	}

	return S_OK;
}

HRESULT ShaderManager::LoadCompiledVertexShader(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, LPCWSTR fileName, ShaderData& shader)
{
	HRESULT result;
	auto VertexBytecode = DX::ReadData(fileName);

	Device->CreateVertexShader(VertexBytecode.data(), VertexBytecode.size(), NULL, &shader.VertexShader);

	DeviceContext->VSSetShader(shader.VertexShader, 0, 0);

	ID3D11ShaderReflection* vShaderReflection = nullptr;
	D3DReflect(VertexBytecode.data(), VertexBytecode.size(), IID_ID3D11ShaderReflection, (void**)&vShaderReflection);

	D3D11_SHADER_DESC shaderDesc;
	vShaderReflection->GetDesc(&shaderDesc);

	auto paramDesc = new D3D11_SIGNATURE_PARAMETER_DESC[shaderDesc.InputParameters]{ 0 };
	for (UINT i = 0; i < shaderDesc.InputParameters; i++)
	{
		vShaderReflection->GetInputParameterDesc(i, &paramDesc[i]);
	}

	auto ied = new D3D11_INPUT_ELEMENT_DESC[shaderDesc.InputParameters]{ 0 };
	for (size_t i = 0; i < shaderDesc.InputParameters; i++)
	{
		ied[i].SemanticName = paramDesc[i].SemanticName;
		ied[i].SemanticIndex = paramDesc[i].SemanticIndex;

		if (paramDesc[i].ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
		{
			switch (paramDesc[i].Mask)
			{
			case 1:
				ied[i].Format = DXGI_FORMAT_R32_FLOAT;
				break;

			case 3:
				ied[i].Format = DXGI_FORMAT_R32G32_FLOAT;
				break;

			case 7:
				ied[i].Format = DXGI_FORMAT_R32G32B32_FLOAT;
				break;

			case 15:
				ied[i].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
				break;

			default:
				break;
			}
		}

		ied[i].InputSlot = 0;
		ied[i].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		ied[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		ied[i].InstanceDataStepRate = 0;

	}


	result = Device->CreateInputLayout(ied, shaderDesc.InputParameters, VertexBytecode.data(), VertexBytecode.size(), &shader.InputLayout);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to create input layout\n");
		return result;
	}
	OutputDebugString(L"Successfully created input layout\n");

	DeviceContext->IASetInputLayout(shader.InputLayout);

	delete[] paramDesc;
	delete[] ied;

	return S_OK;
}

HRESULT ShaderManager::LoadCompiledPixelShader(ID3D11Device* Device, LPCWSTR fileName, ShaderData& shader)
{
	HRESULT result;

	auto PixelBytecode = DX::ReadData(fileName);

	result = Device->CreatePixelShader(PixelBytecode.data(), PixelBytecode.size(), NULL, &shader.PixelShader);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to create pixel shader\n");
		return result;
	}

	return S_OK;
}

HRESULT ShaderManager::CreateShaders(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext)
{
	HRESULT result;

	// Default shader
	if (m_shaders.find("default") != m_shaders.end())
	{
		OutputDebugString(L"Shader already exists\n");
		return E_FAIL;
	}

	ShaderData* shader = new ShaderData();
	result = LoadVertexShader(Device, DeviceContext, L"VertexShader.hlsl", "main", *shader);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to load vertex shader\n");
		return result;
	}

	result = LoadPixelShader(Device, L"PixelShader.hlsl", "main", *shader);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to load pixel shader\n");
		return result;
	}
	m_shaders["default"] = shader;

	// Skybox shader
	if (m_shaders.find("skybox") != m_shaders.end())
	{
		OutputDebugString(L"Shader already exists\n");
		return E_FAIL;
	}

	shader = new ShaderData();
	result = LoadPixelShader(Device, L"SkyboxPixelShader.hlsl", "main", *shader);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to load pixel shader\n");
		return result;
	}

	result = LoadVertexShader(Device, DeviceContext, L"SkyboxVertexShader.hlsl", "main", *shader);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to load vertex shader\n");
		return result;
	}


	m_shaders["skybox"] = shader;


	return S_OK;
}

ShaderData* ShaderManager::GetShader(const std::string& shaderName)
{
	if (m_shaders.find(shaderName) == m_shaders.end())
		return nullptr;

	return m_shaders[shaderName];
}

#pragma once

#include <d3d11.h>

struct ShaderData
{
	ID3D11InputLayout*  InputLayout = nullptr;
	ID3D11VertexShader* VertexShader = nullptr;
	ID3D11PixelShader*  PixelShader = nullptr;

	ShaderData()
	{
		InputLayout = nullptr;
		VertexShader = nullptr;
		PixelShader = nullptr;
	};

	ShaderData(ID3D11InputLayout* il, ID3D11VertexShader* vs, ID3D11PixelShader* ps)
	{
		InputLayout = il;
		VertexShader = vs;
		PixelShader = ps;
	}

	~ShaderData()
	{
		if (VertexShader)	VertexShader->Release();
		if (PixelShader)	PixelShader->Release();
		if (InputLayout)	InputLayout->Release();
	}
};
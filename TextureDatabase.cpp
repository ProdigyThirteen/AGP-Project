#include "TextureDatabase.h"
#include "StaticUtils.h"
#include <d3d11.h>
#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>

void TextureDatabase::LoadTextures(const std::string& filepath, ID3D11Device* device, ID3D11DeviceContext* devContext)
{
	std::vector<std::string> bmpTextures = StaticUtils::GetFilesInDirectory(filepath, ".bmp");
	std::vector<std::string> pngTextures = StaticUtils::GetFilesInDirectory(filepath, ".png");
	std::vector<std::string> jpgTextures = StaticUtils::GetFilesInDirectory(filepath, ".jpg");

	for (std::string& texture : bmpTextures)
	{
		std::wstring wTexture = std::wstring(texture.begin(), texture.end());
		ID3D11ShaderResourceView* srv;
		DirectX::CreateWICTextureFromFile(device, devContext, wTexture.c_str(), nullptr, &srv);
		m_Textures[texture] = srv;
	}

	for (std::string& texture : pngTextures)
	{
		std::wstring wTexture = std::wstring(texture.begin(), texture.end());
		ID3D11ShaderResourceView* srv;
		DirectX::CreateWICTextureFromFile(device, devContext, wTexture.c_str(), nullptr, &srv);
		m_Textures[texture] = srv;
	}

	for (std::string& texture : jpgTextures)
	{
		std::wstring wTexture = std::wstring(texture.begin(), texture.end());
		ID3D11ShaderResourceView* srv;
		DirectX::CreateWICTextureFromFile(device, devContext, wTexture.c_str(), nullptr, &srv);
		m_Textures[texture] = srv;
	}
}

ID3D11ShaderResourceView* TextureDatabase::CreateSkyboxTexture(const std::string& textureName, ID3D11Device* device, ID3D11DeviceContext* devContext)
{
	if (m_Textures.find(textureName) != m_Textures.end())
	{
		return m_Textures[textureName];
	}

	std::string a = "textures/" + textureName + ".dds";
	const std::wstring b = std::wstring(a.begin(), a.end());
	const wchar_t* c = b.c_str();

	ID3D11ShaderResourceView* srv;
	HRESULT res = DirectX::CreateDDSTextureFromFile(device, c, NULL, &srv);
	if (FAILED(res))
	{
		OutputDebugString(L"Failed to load skybox texture\n");
		return nullptr;
	}

	m_Textures[textureName] = srv;

	return srv;
}

ID3D11ShaderResourceView* TextureDatabase::GetTexture(const std::string& aName)
{
	if (m_Textures.find(aName) == m_Textures.end())
	{
		return nullptr;
	}

	return m_Textures[aName];
}

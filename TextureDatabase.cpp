#include "TextureDatabase.h"
#include "StaticUtils.h"
#include <d3d11.h>
#include <WICTextureLoader.h>

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

ID3D11ShaderResourceView* TextureDatabase::GetTexture(const std::string& aName)
{
	return nullptr;
}

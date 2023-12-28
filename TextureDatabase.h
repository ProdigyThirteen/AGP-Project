#pragma once
#include <map>
#include <string>

// Forward declarations
class ID3D11ShaderResourceView;
class ID3D11Device;
class ID3D11DeviceContext;

class TextureDatabase
{
private:
	std::map<std::string, ID3D11ShaderResourceView*> m_Textures;

	TextureDatabase() = default;
	TextureDatabase(const TextureDatabase&) = delete;
	TextureDatabase& operator=(const TextureDatabase&) = delete;

public:
	static TextureDatabase& GetInstance()
	{
		static TextureDatabase instance;
		return instance;
	}

	void LoadTextures(const std::string& filepath, ID3D11Device* device, ID3D11DeviceContext* devContext);
	ID3D11ShaderResourceView* GetTexture(const std::string& aName);
};


#pragma once

#include <map>
#include <string>

// Forward declarations
struct Material;

class MaterialDatabase
{
private:
	static std::map<std::string, Material*> m_Materials;

	MaterialDatabase() = default;
	MaterialDatabase(const MaterialDatabase&) = delete;
	MaterialDatabase& operator=(const MaterialDatabase&) = delete;

public:

	~MaterialDatabase() = default;

	static MaterialDatabase& GetInstance()
	{
		static MaterialDatabase instance;
		return instance;
	}

	void CreateNewMaterial(const std::string& materialName, const std::string& shaderName, const std::string& textureName);
	void CreateSkyboxMaterial(const std::string& materialName, const std::string& shaderName, const std::string& textureName);
	Material* GetMaterial(const std::string& materialName);
};


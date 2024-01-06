#include "MaterialDatabase.h"

#include "ShaderManager.h"
#include "TextureDatabase.h"
#include "Material.h"

std::map<std::string, Material*> MaterialDatabase::m_Materials;

void MaterialDatabase::CreateNewMaterial(const std::string& materialName, const std::string& shaderName, const std::string& textureName)
{
	Material* material = new Material(
		TextureDatabase::GetInstance().GetTexture(textureName),
		ShaderManager::GetInstance().GetShader(shaderName));

	m_Materials[materialName] = material;
}

void MaterialDatabase::CreateSkyboxMaterial(const std::string& materialName, const std::string& shaderName, const std::string& textureName)
{
	Material* material = new Material(
		TextureDatabase::GetInstance().GetTexture(textureName),
		ShaderManager::GetInstance().GetShader(shaderName));

	m_Materials[materialName] = material;
}

Material* MaterialDatabase::GetMaterial(const std::string& materialName)
{
	return m_Materials[materialName];
}

void MaterialDatabase::ReleaseMaterials()
{
	for (auto& material : m_Materials)
	{
		delete material.second;
		material.second = nullptr;
	}
	m_Materials.clear();
}

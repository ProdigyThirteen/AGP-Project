#include "MeshDatabase.h"
#include "Renderer.h"
#include "StaticUtils.h"

MeshDatabase::~MeshDatabase()
{
	OutputDebugStringA("MeshDatabase destructor called\n");

	for (auto& mesh : m_meshes)
	{
		delete mesh.second;
	}
}

void MeshDatabase::LoadMeshes(std::string filename, Renderer* Renderer)
{
	// Get list of every .obj file in the directory
	std::vector<std::string> files = StaticUtils::GetFilesInDirectory(filename, ".obj");

	// Load each mesh
	for (auto& file : files)
	{
		std::string c = filename + file;
		const char* c2 = c.c_str();
		ObjFileModel* mesh = new ObjFileModel((char*)c2, Renderer->GetDevice(), Renderer->GetDeviceContext());
		m_meshes[file.c_str()] = mesh;
	}
}

ObjFileModel* MeshDatabase::GetMesh(const char* name)
{
	return m_meshes[name];
}

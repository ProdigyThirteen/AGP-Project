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
	for (size_t i = 0; i < files.size(); ++i)
	{
		std::string c = filename + files[i];
		const char* c2 = c.c_str();
		ObjFileModel* mesh = new ObjFileModel((char*)c2, Renderer->GetDevice(), Renderer->GetDeviceContext());
		std::string meshName = files[i].substr(0, files[i].find_last_of("."));
		m_meshes[meshName] = mesh;
	}
}

ObjFileModel* MeshDatabase::GetMesh(std::string name)
{
	return m_meshes[name];
}

#pragma once
#include <map>
#include "objfilemodel.h"

class Renderer;

class MeshDatabase
{
private:
	std::map<const char*, ObjFileModel*> m_meshes;

	MeshDatabase() = default;
	MeshDatabase(const MeshDatabase& other) = delete;
	MeshDatabase& operator=(const MeshDatabase& other) = delete;

public:
	static MeshDatabase& GetInstance()
	{
		static MeshDatabase instance;
		return instance;
	}
	~MeshDatabase();

	void LoadMeshes(std::string filename, Renderer* Renderer);
	ObjFileModel* GetMesh(const char* name);

};


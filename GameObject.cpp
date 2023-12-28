#include "GameObject.h"
#include "MeshDatabase.h"
#include "TextureDatabase.h"

GameObject::GameObject(const char* MeshName, const char* TextureName)
{
	m_ObjectMesh = MeshDatabase::GetInstance().GetMesh(MeshName);
	m_Texture	 = TextureDatabase::GetInstance().GetTexture(TextureName);
}

void GameObject::Draw()
{

}

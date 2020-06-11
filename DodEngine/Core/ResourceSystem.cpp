#include "ResourceSystem.h"

ResourceSystem ResourceSystem::m_ResourceSystem;
DU32 ResourceSystem::m_MeshID = 1;

DU32 ResourceSystem::CreateMesh(const std::vector<DVertex> vertices)
{
	DU32 newID = m_MeshID++;
	Renderable mesh(vertices);
	m_Meshes.insert(std::make_pair(newID, mesh));
	return newID;
}

void ResourceSystem::RemoveMesh(DU32 meshID)
{
	m_Meshes.erase(meshID);
}

Renderable* ResourceSystem::GetMesh(DU32 meshID)
{
	std::map<DU32, Renderable>::iterator it = m_Meshes.find(meshID);
	if (it == m_Meshes.end())
	{
		return nullptr;
	}
	return &it->second;
}
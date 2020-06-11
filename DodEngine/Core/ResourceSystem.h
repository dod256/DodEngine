#pragma once

#include <map>
#include <vector>

#include "precomp.h"
#include "Render\Renderable.h"

#define DResourceSystem ResourceSystem::GetResourceSystem()

class ResourceSystem
{
public:
	static ResourceSystem& GetResourceSystem() { return m_ResourceSystem; };
	Renderable* GetMesh(DU32 meshID);
	DU32 CreateMesh(const std::vector<DVertex> vertices);
	void RemoveMesh(DU32 meshID);
private:
	static ResourceSystem m_ResourceSystem;
	static DU32 m_MeshID;
	std::map<DU32, Renderable> m_Meshes;
};


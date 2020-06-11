#include "DPolygon.h"
#include "RenderManager.h"
#include "..\ResourceSystem.h"

void DPolygon::Draw() const
{
	DRenderManager.Draw(m_MeshID);
}

DPolygon::DPolygon(const std::vector<DVertex>& vertices)
{
	m_Vertices = std::vector<DVertex>(vertices.begin(), vertices.end());
	m_MeshID = DResourceSystem.CreateMesh(m_Vertices);
}

DPolygon::DPolygon(const DPolygon& polygon)
{
	m_Vertices = std::vector<DVertex>(polygon.m_Vertices.begin(), polygon.m_Vertices.end());
	m_MeshID = DResourceSystem.CreateMesh(m_Vertices);
}

DPolygon& DPolygon::operator=(const DPolygon& polygon)
{
	DResourceSystem.RemoveMesh(m_MeshID);
	m_Vertices = std::vector<DVertex>(polygon.m_Vertices.begin(), polygon.m_Vertices.end());
	m_MeshID = DResourceSystem.CreateMesh(m_Vertices);
	return *this;
}

void DPolygon::SetColor(Color color)
{
	for (DU32 i = 0; i < m_Vertices.size(); ++i)
	{
		m_Vertices[i].SetColor(DVec4(color.GetR(), color.GetG(), color.GetB(), color.GetA()));
		if (Renderable* renderable = DResourceSystem.GetMesh(m_MeshID))
		{
			renderable->SetColor(color);
		}
	}
}
#include "DArea.h"
#include "Renderer.h"

void DArea::Draw(const Shader& shader) const
{
	m_OpenGLArea.Draw(shader);
}

DArea::DArea(std::vector<DVec4> vertices, Color color)
{
	m_Color = color;
	m_Vertices = std::vector<DVec4>(vertices.begin(), vertices.end());
}

DArea::DArea(const DArea& anotherArea)
{
	m_Color = anotherArea.m_Color;
	m_Vertices = std::vector<DVec4>(anotherArea.m_Vertices.begin(), anotherArea.m_Vertices.end());
}

void DArea::Init()
{
	std::vector<DU32> indices;
	for (DU32 i = 1; i < m_Vertices.size() - 1; ++i)
	{
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);
	}
	std::vector<Vertex> v;
	for (int i = 0; i < m_Vertices.size(); ++i)
	{
		std::pair<DFloat, DFloat> pair = Renderer::WorldCoordToViewportCoord(std::make_pair(m_Vertices[i][0], m_Vertices[i][1]));
		v.push_back(Vertex(pair.first, pair.second));
	}
	m_OpenGLArea = PrimitiveFigure(v, indices, m_Color);
	m_OpenGLArea.Init();
}

void DArea::SetColor(Color newValue)
{
	m_Color = newValue;
	m_OpenGLArea.SetColor(m_Color);
};

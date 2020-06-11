#include "ColorSelection.h"
#include <algorithm>
#include <iostream>
#include "..\Core\Render\Renderer.h"
#include "..\Core\Math\MathHelper.h"

ColorSelection::ColorSelection(const std::vector<DVertex>& vertices, std::function<void(Color color)>& onClickFunc, Color color)
{
	m_OnClickFunc = onClickFunc;
	m_Polygon = DPolygon(vertices);
	m_Color = color;
}

void ColorSelection::OnClick(float mouseXPos, float mouseYPos) const
{
	std::pair<float, float> newCoord = Renderer::MouseToWorld(std::make_pair(mouseXPos, mouseYPos));
	const std::vector<DVertex>& vertices = m_Polygon.GetVertices();
	std::vector<DPoint2> polygon;
	for (const DVertex& vertex : vertices)
	{
		polygon.push_back(DPoint2(vertex.GetPosition()[0], vertex.GetPosition()[1]));
	}
	if (MathHelper::IsInPolygon(DPoint2(newCoord.first, newCoord.second), polygon))
	{
		m_OnClickFunc(m_Color);
	}
}

void ColorSelection::Draw() const
{
	m_Polygon.Draw();
}

void ColorSelection::InitTexture(const char* fileName)
{
	//m_Polygon.InitTexture(fileName);
}

void ColorSelection::Init()
{
	//m_Polygon.Init();
}
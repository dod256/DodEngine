#include "Button.h"
#include <algorithm>
#include <iostream>

#include "Render\Renderer.h"
#include "Math\MathHelper.h"

Button::Button(std::vector<DVec4> vertices, Color color, std::function<void()> onClickFunc)
{
	m_OnClickFunc = onClickFunc;
	m_Polygon = DPolygon(vertices, color);
}

Button::Button(const std::vector<DVertex>& vertices, std::function<void()> onClickFunc)
{
	m_OnClickFunc = onClickFunc;
	m_Polygon = DPolygon(vertices);
}

void Button::OnClick(float mouseXPos, float mouseYPos) const
{
	//ToDo Is Inside Polygon
	std::pair<float, float> newCoord = Renderer::MouseToWorld(std::make_pair(mouseXPos, mouseYPos));
	const std::vector<DVertex>& vertices = m_Polygon.GetVertices();
	std::vector<DPoint2> polygon;
	for (const DVertex& vertex : vertices)
	{
		polygon.push_back(DPoint2(vertex.GetPosition()[0], vertex.GetPosition()[1]));
	}
	if (MathHelper::IsInPolygon(DPoint2(newCoord.first, newCoord.second), polygon))
	//if (vertices[1].GetPosition()[0] <= newCoord.first && newCoord.first <= vertices[3].GetPosition()[0] &&
	//	vertices[1].GetPosition()[1] <= newCoord.second && newCoord.second <= vertices[3].GetPosition()[1])
	{
		m_OnClickFunc();
	}
}

void Button::Draw(const Shader& shader) const
{
	m_Polygon.Draw(shader);
}

void Button::Init()
{
	m_Polygon.Init();
}
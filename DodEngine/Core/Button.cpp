#include "Button.h"
#include <algorithm>
#include <iostream>

#include "Render\Renderer.h"
#include "Math\MathHelper.h"

Button::Button(const std::vector<DVertex>& vertices, std::function<void()>& onClickFunc)
{
	m_OnClickFunc = onClickFunc;
	m_Polygon = DPolygon(vertices);
}

void Button::OnClick(float mouseXPos, float mouseYPos) const
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
		m_OnClickFunc();
	}
}

void Button::Draw() const
{
	m_Polygon.Draw();
}

void Button::InitTexture(const char* fileName)
{
	//m_Polygon.InitTexture(fileName);
}

void Button::Init()
{
	//m_Polygon.Init();
}
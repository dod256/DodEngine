#include "Text.h"
#include "RenderManager.h"
#include "Renderer.h"
#include "..\Math\MathHelper.h"

Text::Text(std::string text, DVec4 color, DFloat x, DFloat y, DFloat scale) : m_Text(text), m_X(x), m_Y(y), m_Scale(scale), m_Color(color)
{
}

void Text::Draw() const
{
	DRenderManager.RenderText(m_Text, m_X, m_Y, m_Scale, m_Color);
}

void Text::AddOnClick(std::function<void()>& onClickFunc)
{
	m_OnClickFunc = onClickFunc;
}

void Text::OnClick(float mouseXPos, float mouseYPos) const
{
	std::pair<float, float> newCoord = Renderer::MouseToWorld(std::make_pair(mouseXPos, mouseYPos));
	const std::vector<DVertex>& vertices = DRenderManager.TextPolygon(m_Text, m_X, m_Y, m_Scale);
	std::vector<DPoint2> polygon;
	for (const DVertex& vertex : vertices)
	{
		polygon.push_back(DPoint2(vertex.GetPosition()[0], vertex.GetPosition()[1]));
	}
	if (MathHelper::IsInPolygon(DPoint2(newCoord.first, newCoord.second), polygon))
	{
		if (m_OnClickFunc)
		{
			m_OnClickFunc();
		}

	}
}

#include "ColorSelection.h"
#include "Field.h"
#include "..\Core\Render\Renderer.h"


ColorSelection::ColorSelection(std::vector<Vertex> points, std::vector<unsigned int> indices, Color color, Field* field) : IClickable(),PrimitiveFigure(points, indices, color)
{
	m_Field = field;
}

ColorSelection::ColorSelection(const ColorSelection& button) : IClickable(), PrimitiveFigure(button)
{
	m_Field = button.m_Field;
}

void ColorSelection::OnClick(float mouseXPos, float mouseYPos) const
{
	std::pair<float, float> newCoord = Renderer::MouseToViewport(std::make_pair(mouseXPos, mouseYPos));
	std::vector<Vertex> vertices = GetVertices();
	if (vertices[0].GetX() <= newCoord.first && newCoord.first <= vertices[2].GetX() &&
		vertices[0].GetY() <= newCoord.second && newCoord.second <= vertices[2].GetY())
	{
		if (m_Field)
		{
			m_Field->PlayerTurn(GetColor());
		}
	}
}

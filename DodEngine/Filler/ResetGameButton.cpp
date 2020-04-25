#include "ResetGameButton.h"
#include "..\Core\Render\Renderer.h"
#include "GameLoop.h"

ResetGameButton::ResetGameButton(std::vector<Vertex> points, std::vector<unsigned int> indices, Color color, GameLoop* gameLoop) : IClickable(), PrimitiveFigure(points, indices, color)
{
	m_GameLoop = gameLoop;
}

ResetGameButton::ResetGameButton(const ResetGameButton& button) : IClickable(), PrimitiveFigure(button)
{
	m_GameLoop = button.m_GameLoop;
}

void ResetGameButton::OnClick(float mouseXPos, float mouseYPos) const
{
	std::pair<float, float> newCoord = Renderer::MouseCoordToViewportCoord(std::make_pair(mouseXPos, mouseYPos));
	std::vector<Vertex> vertices = GetVertices();
	if (vertices[0].GetX() <= newCoord.first && newCoord.first <= vertices[2].GetX() &&
		vertices[0].GetY() <= newCoord.second && newCoord.second <= vertices[2].GetY())
	{
		if (m_GameLoop)
		{
			m_GameLoop->Reset();
		}
	}
}
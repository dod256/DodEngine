#pragma once
#include "..\Core\Render\PrimitiveFigure.h"
#include "..\Core\IClickable.h"

class GameLoop;

class ResetGameButton : public IClickable, public PrimitiveFigure
{
public:
	ResetGameButton(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Color color, GameLoop* gameLoop);
	ResetGameButton(const ResetGameButton& button);
	void OnClick(float mouseXPos, float mouseYPos) const;
private:
	GameLoop* m_GameLoop;
};


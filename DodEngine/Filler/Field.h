#pragma once
#include "..\Core\Constants.h"
#include "..\Core\Render\IDrawable.h"
#include "..\Core\Color.h"

class Hex;

class Field : public IDrawable
{
public:
	void Draw(const Shader& shader) const override;
	void Reset();
	void PlayerTurn(Color newColor);
	unsigned int PlayerScore(unsigned int player);
	void Init();
	Field();
	~Field();
private:
	bool Turn(unsigned int player1, unsigned int player2, Color newColor);
	std::vector<std::vector<Hex> > m_Hexes;
	std::vector<std::pair<unsigned int, unsigned int> > m_StartingPositions;
};


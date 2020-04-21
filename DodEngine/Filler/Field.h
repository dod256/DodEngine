#pragma once
#include "..\Core\Constants.h"
#include "..\Core\Render\IDrawable.h"
#include "..\Core\Color.h"
#include "..\Core\Render\PrimitiveFigure.h"
#include "..\Core\IDSUMember.h"

class Field : public IDrawable
{
public:

	class Hex : public PrimitiveFigure, public IDSUMember
	{
	public:
		Hex(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Color color);
		Hex(const Hex& hex);
	};

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
	std::vector<Color> m_Colors;
};


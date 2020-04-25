#pragma once
#include "..\Core\Constants.h"
#include "..\Core\Render\IDrawable.h"
#include "..\Core\Render\Color.h"
#include "..\Core\Render\DArea.h"
#include "..\Core\IDSUMember.h"

class Field : public IDrawable
{
public:

	class Hex : public DArea, public IDSUMember
	{
	public:
		Hex(std::vector<DVec4> vertices, Color color = Color(0.0f, 0.0f, 0.0f, 1.0f));
		Hex(const Hex& hex);
	};

	void Draw(const Shader& shader) const override;
	void Reset();
	void PlayerTurn(Color newColor);
	unsigned int PlayerScore(unsigned int player);
	void Init();
	Field();
	~Field();
	const std::vector<Color>& GetColors() const { return m_Colors; };
private:
	bool Turn(unsigned int player1, unsigned int player2, Color newColor);
	std::vector<std::vector<Hex> > m_Hexes;
	std::vector<std::pair<unsigned int, unsigned int> > m_StartingPositions;
	std::vector<Color> m_Colors;
};


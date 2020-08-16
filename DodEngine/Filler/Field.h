#pragma once
#include "..\Core\Constants.h"
#include "..\Core\Render\IDrawable.h"
#include "..\Core\Render\Color.h"
#include "..\Core\Render\DPolygon.h"
#include "..\Core\IDSUMember.h"
#include "..\Core\Button.h"
#include "ColorSelection.h"
#include "..\Core\Player.h"
#include "..\Core\Scene.h"
#include "..\Core\SceneManager.h"

class Field : public Scene
{
public:

	class Hex : public DPolygon, public IDSUMember
	{
	public:
		Hex(std::vector<DVertex> vertices, Color color = Color(0.0f, 0.0f, 0.0f, 1.0f)) : DPolygon(vertices), IDSUMember() {};
		Hex(const Hex& hex) : DPolygon(hex), IDSUMember(hex) {};
		Color GetColor();
		void SetColor(Color color) override;
	};

	void Update() override;
	void PlayerTurn(Color newColor);
	unsigned int PlayerScore(unsigned int player) const;
	void Init();
	Field();
	~Field();
	const std::vector<Color>& GetColors() const { return m_Colors; };
	void DisableColorSelection();
private:
	void AddColorSelection(float x, float y, float a, float b, Color color);
	bool Turn(unsigned int player1, unsigned int player2, Color newColor);
	std::vector<std::vector<Hex> > m_Hexes;
	std::vector<std::pair<unsigned int, unsigned int> > m_StartingPositions;
	std::vector<Color> m_Colors;

	std::vector<ColorSelection> m_ColorSelections;
	Button m_Reset;
	bool m_IsGameEnded = true;
	std::vector<Player> m_Players;
};


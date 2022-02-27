#include "Filler_Field.h"

#include <cassert>
#include <iostream>

#include"Constants.h"
#include "Core\Render\RenderManager.h"

void Filler_Field::Hex::SetColor(Color color)
{
	DPolygon::SetColor(color);
}

Color Filler_Field::Hex::GetColor()
{
	const std::vector<DVertex>& vertices = GetVertices();
	if (vertices.size() > 0)
	{
		DVec4 color = vertices[0].GetColor();
		return Color(color[0], color[1], color[2], color[3]);
	}
	return Color(0.0f, 0.0f, 0.0f, 1.0f);
}

unsigned int Filler_Field::PlayerScore(unsigned int player) const
{
	unsigned score = 0;
	for (unsigned int i = 0; i < m_Hexes.size(); ++i)
	{
		for (unsigned j = 0; j < m_Hexes[i].size(); ++j)
		{
			if (m_Hexes[m_StartingPositions[player].first][m_StartingPositions[player].second].FindSet() == m_Hexes[i][j].FindSet())
			{
				++score;
			}
		}
	}
	return score;
}

Filler_Field::~Filler_Field()
{
	for (std::vector<Hex>& column : m_Hexes)
	{
		column.clear();
	}
}

void Filler_Field::Init()
{
	m_Hexes.clear();
	m_StartingPositions.clear();
	m_Colors.clear();
	m_ColorSelections.clear();
	m_Players.clear();

	Player::ResetNumberOfPlayers();
	m_Players.push_back(Player("Player1", false));
	m_Players.push_back(Player("AI"));
	m_StartingPositions.push_back(std::make_pair(0, 0));
	m_StartingPositions.push_back(std::make_pair(FIELD_SIZE_X - 1, FIELD_SIZE_Y - 1));
	m_IsGameEnded = false;
	m_Colors.push_back(Color(0.0f, 0.0f, 1.0f, 1.0f));
	m_Colors.push_back(Color(0.0f, 1.0f, 0.0f, 1.0f));
	m_Colors.push_back(Color(1.0f, 0.0f, 0.0f, 1.0f));
	m_Colors.push_back(Color(0.0f, 1.0f, 1.0f, 1.0f));
	m_Colors.push_back(Color(1.0f, 1.0f, 0.0f, 1.0f));
	m_Colors.push_back(Color(1.0f, 0.0f, 1.0f, 1.0f));

	for (DU32 i = 0; i < m_Colors.size(); ++i)
	{
		AddColorSelection(140.0f + i * 140.0f, 30.0f, 40.0f, 10.0f, m_Colors[i]);
	}

	std::vector<DVertex> resetVertices(4);
	resetVertices[0].SetPosition(DVec4(120.0f, DEFAULT_WINDOWS_HEIGHT - 40.0f, 0.0f, 1.0f));
	resetVertices[1].SetPosition(DVec4(120.0f, DEFAULT_WINDOWS_HEIGHT - 10.0f, 0.0f, 1.0f));
	resetVertices[2].SetPosition(DVec4(150.0f, DEFAULT_WINDOWS_HEIGHT - 10.0f, 0.0f, 1.0f));
	resetVertices[3].SetPosition(DVec4(150.0f, DEFAULT_WINDOWS_HEIGHT - 40.0f, 0.0f, 1.0f));
	resetVertices[0].SetColor(DVec4(1.0f, 0.0f, 0.0f, 1.0f));
	resetVertices[1].SetColor(DVec4(0.0f, 1.0f, 0.0f, 1.0f));
	resetVertices[2].SetColor(DVec4(0.0f, 0.0f, 1.0f, 1.0f));
	resetVertices[3].SetColor(DVec4(1.0f, 1.0f, 0.0f, 1.0f));
	resetVertices[0].SetTexturePosition(DVec2(1.0f, 1.0f));
	resetVertices[1].SetTexturePosition(DVec2(1.0f, 0.0f));
	resetVertices[2].SetTexturePosition(DVec2(0.0f, 0.0f));
	resetVertices[3].SetTexturePosition(DVec2(0.0f, 1.0f));
	std::function<void()> Filler_FieldReset = std::bind(&Filler_Field::Init, this);
	//std::function<void()> Filler_FieldReset = std::bind(&GameLoop::Reset, this);
	m_Reset = Button(resetVertices, Filler_FieldReset);


	DFloat a = 8.0f;
	DFloat b = 12.0f;
	DFloat x = 100.0f + b;

	for (unsigned int i = 0; i < FIELD_SIZE_X; ++i)
	{
		DFloat y = 60.0f + a;
		if (i % 2)
		{
			y += a;
		}
		m_Hexes.push_back(std::vector<Hex>());
		for (unsigned int j = 0; j < FIELD_SIZE_Y; ++j)
		{
			std::vector<DVertex> vertices(6);
			vertices[0].SetPosition(DVec4(x - b, y, 0.0f, 1.0f));
			vertices[1].SetPosition(DVec4(x - a, y + a, 0.0f, 1.0f));
			vertices[2].SetPosition(DVec4(x + a, y + a, 0.0f, 1.0f));
			vertices[3].SetPosition(DVec4(x + b, y, 0.0f, 1.0f));
			vertices[4].SetPosition(DVec4(x + a, y - a, 0.0f, 1.0f));
			vertices[5].SetPosition(DVec4(x - a, y - a, 0.0f, 1.0f));

			Color color = m_Colors[rand() % m_Colors.size()];
			for (int i = 0; i < 6; ++i)
			{
				vertices[i].SetColor(DVec4(color.GetR(), color.GetG(), color.GetB(), color.GetA()));
			}

			m_Hexes[i].push_back(Hex(vertices, color));

			if (j > 0)
			{
				if (m_Hexes[i][j].GetColor() == m_Hexes[i][j - 1].GetColor())
				{
					m_Hexes[i][j].UnionSets(&m_Hexes[i][j - 1]);
					//std::cout << i << " " << j << " and " << i << " " << j - 1 << std::endl;
				}
			}

			if (i > 0)
			{
				if (m_Hexes[i][j].GetColor() == m_Hexes[i - 1][j].GetColor())
				{
					m_Hexes[i][j].UnionSets(&m_Hexes[i - 1][j]);
					//std::cout << i << " " << j << " and " << i - 1 << " " << j << std::endl;
				}
				int k = -1;
				if (i % 2)
				{
					k *= -1;
				}

				if (j + k > 0 && j + k < FIELD_SIZE_Y)
				{
					if (m_Hexes[i][j].GetColor() == m_Hexes[i - 1][j + k].GetColor())
					{
						m_Hexes[i][j].UnionSets(&m_Hexes[i - 1][j + k]);
						//std::cout << i << " " << j << " and " << i - 1 << " " << j + k << std::endl;
					}
				}
			}

			y += 2 * a;
		}
		x += b + a;
	}
}

Filler_Field::Filler_Field() : Scene(SceneID::SceneID_GameField)
{
	m_Players.reserve(2);
	m_StartingPositions.reserve(2);
	m_Colors.reserve(6);
	m_ColorSelections.reserve(6);
}

void Filler_Field::AddColorSelection(float x, float y, float a, float b, Color color)
{
	std::vector<DVertex> vertices(4);
	vertices[0].SetPosition(DVec4(x - a, y - b, 0.0f, 1.0f));
	vertices[1].SetPosition(DVec4(x + a, y - b, 0.0f, 1.0f));
	vertices[2].SetPosition(DVec4(x + a, y + b, 0.0f, 1.0f));
	vertices[3].SetPosition(DVec4(x - a, y + b, 0.0f, 1.0f));
	vertices[0].SetColor(DVec4(color.GetR(), color.GetG(), color.GetB(), color.GetA()));
	vertices[1].SetColor(DVec4(color.GetR(), color.GetG(), color.GetB(), color.GetA()));
	vertices[2].SetColor(DVec4(color.GetR(), color.GetG(), color.GetB(), color.GetA()));
	vertices[3].SetColor(DVec4(color.GetR(), color.GetG(), color.GetB(), color.GetA()));

	std::function<void(Color color)> Filler_FieldPlayerTurn = std::bind(&Filler_Field::PlayerTurn, this, color);

	m_ColorSelections.push_back(ColorSelection(vertices, Filler_FieldPlayerTurn, color));
	m_ColorSelections[m_ColorSelections.size() - 1].Init();
}

void Filler_Field::Update()
{

	if (!m_IsGameEnded)
	{
		for (const ColorSelection& colorSelection : m_ColorSelections)
		{
			colorSelection.Draw();
		}
	}

	m_Reset.Draw();

	for (const std::vector<Hex>& column : m_Hexes)
	{
		for (const Hex& hex : column)
		{
			hex.Draw();
		}
	}

	for (const Player& player : m_Players)
	{
		if (PlayerScore(player.GetID()) > 600)
		{
			std::string s = player.GetName() + " has won!";
			DRenderManager.RenderText(s, 600.0f, 560.0f, 0.4f, DVec4(1.0, 1.0f, 1.0f, 1.0f));
			DisableColorSelection();
			break;
		}
	}


	float y = 580.0f;
	for (const Player& player : m_Players)
	{
		std::string s = player.GetName() + ": " + std::to_string(PlayerScore(player.GetID()));
		DRenderManager.RenderText(s, 20.0f, y, 0.3f, DVec4(1.0, 1.0f, 1.0f, 1.0f));
		y -= 20.0f;
	}
}

void Filler_Field::PlayerTurn(Color newColor)
{
	bool successfulTurn = Turn(0, 1, newColor);	
	if (!successfulTurn)
	{
		return;
	}

	Color color;
	do
	{
		unsigned i = rand() % 6;
		switch (i)
		{
		case 0:
			color = Color(0.0f, 0.0f, 1.0f, 1.0f);
			break;
		case 1:
			color = Color(0.0f, 1.0f, 0.0f, 1.0f);
			break;
		case 2:
			color = Color(1.0f, 0.0f, 0.0f, 1.0f);
			break;
		case 3:
			color = Color(0.0f, 1.0f, 1.0f, 1.0f);
			break;
		case 4:
			color = Color(1.0f, 1.0f, 0.0f, 1.0f);
			break;
		case 5:
			color = Color(1.0f, 0.0f, 1.0f, 1.0f);
			break;
		default:
			color = Color(0.5f, 0.5f, 1.0f, 1.0f);
		}
	}
	while (color == m_Hexes[m_StartingPositions[0].first][m_StartingPositions[0].second].GetColor() || color == m_Hexes[m_StartingPositions[1].first][m_StartingPositions[1].second].GetColor());
	Turn(1, 0, color);
}

bool Filler_Field::Turn(unsigned int player1, unsigned int player2, Color newColor)
{
	//std::cout << newColor.GetR() << " " << newColor.GetG() << " " << newColor.GetB() << " " << newColor.GetA() << " " << std::endl;
	if (newColor == m_Hexes[m_StartingPositions[player1].first][m_StartingPositions[player1].second].GetColor() ||
		newColor == m_Hexes[m_StartingPositions[player2].first][m_StartingPositions[player2].second].GetColor())
	{
		return false;
	}
	for (unsigned int i = 0; i < FIELD_SIZE_X; ++i)
	{
		for (unsigned int j = 0; j < FIELD_SIZE_Y; ++j)
		{
			if (m_Hexes[m_StartingPositions[player1].first][m_StartingPositions[player1].second].FindSet() != m_Hexes[i][j].FindSet())
			{				
				continue;
			}

			if (j > 0)
			{
				if (m_Hexes[i][j - 1].GetColor() == newColor)
				{
					m_Hexes[i][j].UnionSets(&m_Hexes[i][j - 1]);
				}

			}

			if (j + 1 < FIELD_SIZE_Y)
			{
				if (m_Hexes[i][j + 1].GetColor() == newColor)
				{
					m_Hexes[i][j].UnionSets(&m_Hexes[i][j + 1]);
				}
			}

			if (i > 0)
			{
				if (m_Hexes[i - 1][j].GetColor() == newColor)
				{
					m_Hexes[i][j].UnionSets(&m_Hexes[i - 1][j]);
				}
				int k = -1;
				if (i % 2)
				{
					k *= -1;
				}

				if (j + k > 0 && j + k < FIELD_SIZE_Y)
				{
					if (m_Hexes[i - 1][j + k].GetColor() == newColor)
					{
						m_Hexes[i][j].UnionSets(&m_Hexes[i - 1][j + k]);
					}
				}
			}

			if (i + 1 < FIELD_SIZE_X)
			{
				if (m_Hexes[i + 1][j].GetColor() == newColor)
				{
					m_Hexes[i][j].UnionSets(&m_Hexes[i + 1][j]);
				}
				int k = -1;
				if (i % 2)
				{
					k *= -1;
				}

				if (j + k > 0 && j + k < FIELD_SIZE_Y)
				{
					if (m_Hexes[i + 1][j + k].GetColor() == newColor)
					{
						m_Hexes[i][j].UnionSets(&m_Hexes[i + 1][j + k]);
					}
				}
			}
		}
	}

	for (unsigned int i = 0; i < m_Hexes.size(); ++i)
	{
		for (unsigned j = 0; j < m_Hexes[i].size(); ++j)
		{
			if (m_Hexes[m_StartingPositions[player1].first][m_StartingPositions[player1].second].FindSet() == m_Hexes[i][j].FindSet())
			{
				m_Hexes[i][j].SetColor(newColor);
			}
		}
	}
	return true;
}

void Filler_Field::DisableColorSelection()
{
	for (ColorSelection& colorSelection : m_ColorSelections)
	{
		colorSelection.SetIsClickDisabled(true);
	}
}

#include "Field.h"
#include <cassert>
#include <iostream>

Field::Hex::Hex(std::vector<DVertex> vertices, Color color) : DPolygon(vertices), IDSUMember()
{
//	m_Color = color;
}

Field::Hex::Hex(const Hex& hex) : DPolygon(hex), IDSUMember(hex)
{
//	m_Color = hex.m_Color;
}

void Field::Hex::SetColor(Color color)
{
	DPolygon::SetColor(color);
//	m_Color = color;
}

Color Field::Hex::GetColor()
{
	const std::vector<DVertex>& vertices = GetVertices();
	if (vertices.size() > 0)
	{
		DVec4 color = vertices[0].GetColor();
		return Color(color[0], color[1], color[2], color[3]);
	}
	return Color(0.0f, 0.0f, 0.0f, 1.0f);
}

void Field::Reset()
{
	m_Hexes.clear();
	m_StartingPositions.clear();
	m_Colors.clear();
	Init();
}

unsigned int Field::PlayerScore(unsigned int player)
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

Field::~Field()
{
	for (std::vector<Hex>& column : m_Hexes)
	{
		column.clear();
	}
}

void Field::Init()
{
	m_Colors.push_back(Color(0.0f, 0.0f, 1.0f, 1.0f));
	m_Colors.push_back(Color(0.0f, 1.0f, 0.0f, 1.0f));
	m_Colors.push_back(Color(1.0f, 0.0f, 0.0f, 1.0f));
	m_Colors.push_back(Color(0.0f, 1.0f, 1.0f, 1.0f));
	m_Colors.push_back(Color(1.0f, 1.0f, 0.0f, 1.0f));
	m_Colors.push_back(Color(1.0f, 0.0f, 1.0f, 1.0f));

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

	for(std::vector<Hex>& column : m_Hexes)
	{
		for(Hex& hex : column)
		{
			hex.Init();
		}
	}

	m_StartingPositions.push_back(std::make_pair(0, 0));
	m_StartingPositions.push_back(std::make_pair(FIELD_SIZE_X - 1, FIELD_SIZE_Y - 1));
}

Field::Field()
{
	m_StartingPositions.reserve(2);
	m_Colors.reserve(6);
}

void Field::Draw(const Shader& shader) const
{
	for (const std::vector<Hex>& column : m_Hexes)
	{
		for (const Hex& hex : column)
		{
			hex.Draw(shader);
		}
	}
}

void Field::PlayerTurn(Color newColor)
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

bool Field::Turn(unsigned int player1, unsigned int player2, Color newColor)
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
				m_Hexes[i][j].Init();
			}
		}
	}
	return true;
}

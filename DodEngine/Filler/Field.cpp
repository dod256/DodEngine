#include "Field.h"
#include "Hex.h"
#include <cassert>
#include <iostream>

void Field::Reset()
{
	m_Hexes.clear();
	m_StartingPositions.clear();
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
	float a = 0.02f;
	float b = 0.04f;

	float x = -0.9f + b;
	for (unsigned int i = 0; i < FIELD_SIZE_X; ++i)
	{
		float y = -0.8f + a;
		if (i % 2)
		{
			y += a;
		}
		m_Hexes.push_back(std::vector<Hex>());
		for (unsigned int j = 0; j < FIELD_SIZE_Y; ++j)
		{
			std::vector<Vertex> vertices;
			vertices.push_back(Vertex(x - b, y));
			vertices.push_back(Vertex(x - a, y + a));
			vertices.push_back(Vertex(x + a, y + a));
			vertices.push_back(Vertex(x + b, y));
			vertices.push_back(Vertex(x + a, y - a));
			vertices.push_back(Vertex(x - a, y - a));

			std::vector<unsigned int> indices = {
				0, 1, 5,
				1, 4, 5,
				1, 2, 4,
				2, 3, 4
			};

			Color color;

			switch (rand() % 6)
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

			m_Hexes[i].push_back(Hex(vertices, indices, color));

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

	m_StartingPositions.push_back(std::make_pair(0, 0));
	m_StartingPositions.push_back(std::make_pair(FIELD_SIZE_X - 1, FIELD_SIZE_Y - 1));
}

Field::Field()
{
}

void Field::Draw(const Shader& shader) const
{
	for (const std::vector<Hex> column : m_Hexes)
	{
		for (Hex hex : column)
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
			}
		}
	}
	return true;
}

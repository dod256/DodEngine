#include "Field.h"
#include <iostream>
#include "Core\Render\RenderManager.h"

Field::~Field()
{
	for (std::vector<Tile>& column : m_Tiles)
	{
		column.clear();
	}
}

void Field::Init(const char* acMapName)
{
	std::ifstream xInputFile(acMapName, std::ios::in | std::ios::binary);
	if (!xInputFile.is_open())
	{
		return;
	}

	unsigned int iX = 0;
	unsigned int iY = 0;

	xInputFile >> iX;
	xInputFile >> iY;

	m_Tiles.clear();

	DFloat fLeftTopCornerX = 100.0f;
	DFloat fLeftTopCornerY = 900.0f;
	DFloat fTileSize = 60;

	for (unsigned int i = 0; i < iX; ++i)
	{
		m_Tiles.push_back(std::vector<Tile>(iY));
	}

	for (unsigned int j = 0; j < iY; ++j)
	{
		DFloat y = fLeftTopCornerY - j * fTileSize;
		for (unsigned int i = 0; i < iX; ++i)
		{
			DFloat x = fLeftTopCornerX + i * fTileSize;
			std::vector<DVertex> vertices(4);
			vertices[0].SetPosition(DVec4(x, y, 0.0f, 1.0f));
			vertices[1].SetPosition(DVec4(x, y + fTileSize, 0.0f, 1.0f));
			vertices[2].SetPosition(DVec4(x + fTileSize, y + fTileSize, 0.0f, 1.0f));
			vertices[3].SetPosition(DVec4(x + fTileSize, y, 0.0f, 1.0f));

			vertices[0].SetTexturePosition(DVec2(0.0f, 0.0f));
			vertices[1].SetTexturePosition(DVec2(0.0f, 1.0f));
			vertices[2].SetTexturePosition(DVec2(1.0f, 1.0f));
			vertices[3].SetTexturePosition(DVec2(1.0f, 0.0f));

			std::string sTextureName;
			int iTileType;
			xInputFile >> iTileType;

			switch (iTileType)
			{
			case 1: sTextureName = "AE_Assets/Snow.jpg"; break;
			case 2: sTextureName = "AE_Assets/Hills.jpg"; break;
			case 3: sTextureName = "AE_Assets/Mountain.jpg"; break;
			case 4: sTextureName = "AE_Assets/Forest1.jpg"; break;
			case 5: sTextureName = "AE_Assets/Forest2.jpg"; break;
			case 6: sTextureName = "AE_Assets/Water1.jpg"; break;
			case 7: sTextureName = "AE_Assets/Water2.jpg"; break;
			case 8: sTextureName = "AE_Assets/Water3.jpg"; break;
			case 9: sTextureName = "AE_Assets/Castle.jpg"; break;
			case 10: sTextureName = "AE_Assets/House.jpg"; break;
			case 11: sTextureName = "AE_Assets/HouseBroken.jpg"; break;
			// ToDo: change to another jpg
			default: sTextureName = "AE_Assets/Snow.jpg"; break;
			}

			Tile xNewTile = Tile(vertices, sTextureName.c_str());
			if ((i + j) % 2)
			{
				xNewTile.SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				xNewTile.SetColor(Color(0.0f, 0.0f, 1.0f, 1.0f));
			}
			m_Tiles[i][j] = xNewTile;
		}
	}
}

Field::Field()
{
}

void Field::Update()
{

	for (const std::vector<Tile>& column : m_Tiles)
	{
		for (const Tile& xTile : column)
		{
			DRenderManager.Draw(xTile);
			//xTile.Draw();
		}
	}
}

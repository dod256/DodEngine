#pragma once
#include "..\Core\Render\IDrawable.h"
#include "..\Core\Render\DPolygon.h"

class Field
{
public:

	class Tile : public Renderable
	{
	public:
		Tile() : Renderable() {};
		Tile(std::vector<DVertex> vertices, const char* fileName) : Renderable(vertices, fileName) {};
		Tile(const Tile& xTile) : Renderable(xTile) {};
	};

	void Update();
	void Init(const char* acMapName);
	Field();
	~Field();
private:
	std::vector<std::vector<Tile> > m_Tiles;
};


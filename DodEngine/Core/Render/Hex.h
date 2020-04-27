#pragma once
#include <vector>
#include "DPolygon.h"

class Hex : public DPolygon
{
public:
	Hex(std::vector<DVec4> vertices, Color color = Color(0.0f, 0.0f, 0.0f, 1.0f));
	Hex(const Hex& hex);
};


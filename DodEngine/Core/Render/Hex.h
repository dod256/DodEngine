#pragma once
#include <vector>
#include "PrimitiveFigure.h"

class Hex : public PrimitiveFigure
{
public:
	Hex(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Color color);
	Hex(const Hex& hex);
};


#pragma once
#include <vector>
#include "..\Core\Render\PrimitiveFigure.h"
#include "..\Core\IDSUMember.h"

class Hex : public PrimitiveFigure, public IDSUMember
{
public:
	Hex(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Color color);
	Hex(const Hex& hex);
};


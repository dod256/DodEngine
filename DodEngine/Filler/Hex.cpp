#pragma once
#include "Hex.h"

Hex::Hex(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Color color) : PrimitiveFigure(vertices, indices, color), IDSUMember()
{
}

Hex::Hex(const Hex& hex) : PrimitiveFigure(hex), IDSUMember(hex)
{
}

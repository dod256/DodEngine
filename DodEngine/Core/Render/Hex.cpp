#pragma once
#include "Hex.h"

Hex::Hex(std::vector<DVec4> vertices, Color color) : DPolygon(vertices, color)
{
}

Hex::Hex(const Hex& hex) : DPolygon(hex)
{
}

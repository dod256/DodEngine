#pragma once
#include "Hex.h"

Hex::Hex(std::vector<DVec4> vertices, Color color) : DArea(vertices, color)
{
}

Hex::Hex(const Hex& hex) : DArea(hex)
{
}

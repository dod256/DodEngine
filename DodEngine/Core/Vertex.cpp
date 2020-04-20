#include "Vertex.h"
#include <cmath>

Vertex::Vertex(float x, float y) : m_X(x), m_Y(y) {}

Vertex::Vertex(const Vertex& vertex)
{
	m_X = vertex.m_X;
	m_Y = vertex.m_Y;
}

bool Vertex::operator == (const Vertex& vertex) const
{
	return std::abs(m_X - vertex.m_X) < EPS && std::abs(m_Y - vertex.m_Y) < EPS;
}
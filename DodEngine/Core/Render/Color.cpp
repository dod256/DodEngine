#include "Color.h"

Color::Color(float r, float g, float b, float a) : m_R(r), m_G(g), m_B(b), m_A(a) {}

bool Color::operator == (const Color& color) const
{
	return m_R == color.m_R && m_G == color.m_G && m_B == color.m_B && m_A == color.m_A;
}

bool Color::operator != (const Color& color) const
{
	return !(operator == (color));
}

Color::Color(const Color& color)
{
	m_R = color.m_R;
	m_G = color.m_G;
	m_B = color.m_B;
	m_A = color.m_A;
}

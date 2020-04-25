#pragma once
class Color
{
public:
	Color() {};
	Color(float r, float g, float b, float a);
	Color(const Color& color);
	float GetR() const { return m_R; };
	float GetG() const { return m_G; };
	float GetB() const { return m_B; };
	float GetA() const { return m_A; };
	bool operator == (const Color& color) const;
	bool operator != (const Color& color) const;
private:
	float m_R = 0.0f;
	float m_G = 0.0f;
	float m_B = 0.0f;
	float m_A = 0.0f;
};


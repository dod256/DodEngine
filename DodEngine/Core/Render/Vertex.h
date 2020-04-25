#pragma once

#define EPS (1e-5)

class Vertex
{
public:
	Vertex(float x, float y);
	Vertex(const Vertex& vertex);
	float GetX() { return m_X; };
	float GetY() { return m_Y; };
	bool operator == (const Vertex& vertex) const;
private:
	float m_X = 0.0f;
	float m_Y = 0.0f;
};


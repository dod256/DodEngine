#pragma once
#include "IDrawable.h"
#include "Vertex.h"
#include "Color.h"

class PrimitiveFigure :	public IDrawable
{
public:
	virtual void Draw(const Shader& shader) const;
	PrimitiveFigure() {};
	PrimitiveFigure(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	PrimitiveFigure(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Color color);
	PrimitiveFigure(const PrimitiveFigure& object);
	~PrimitiveFigure();
	std::vector<Vertex> GetVertices() const { return std::vector<Vertex>(m_Vertices.begin(), m_Vertices.end()); };
	void SetColor(Color color) { m_Color = color; };
	Color GetColor() const { return m_Color; };
	void Init();
protected:
	Color m_Color;
private:
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	unsigned int m_VertexArray = 0;
	unsigned int m_VertexBuffer = 0;
	unsigned int m_ElementBuffer = 0;
};


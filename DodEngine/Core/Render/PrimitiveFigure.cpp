#include "PrimitiveFigure.h"

void PrimitiveFigure::Draw(const Shader& shader) const
{
	shader.SetVec4("ourColor", m_Color.GetR(), m_Color.GetG(), m_Color.GetB(), m_Color.GetA());
	glBindVertexArray(m_VertexArray);
	glDrawElements(GL_TRIANGLES, (int)m_Indices.size(), GL_UNSIGNED_INT, 0);
}

PrimitiveFigure::PrimitiveFigure(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Color color)
{
	m_Vertices = std::vector<Vertex>(vertices.begin(), vertices.end());
	m_Indices = std::vector<unsigned int>(indices.begin(), indices.end());
	m_Color = color;
	Init();
}

PrimitiveFigure::PrimitiveFigure(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	m_Vertices = std::vector<Vertex>(vertices.begin(), vertices.end());
	m_Indices = std::vector<unsigned int>(indices.begin(), indices.end());
	m_Color = Color(0.0f, 0.0f, 0.0f, 1.0f);
	Init();
}

PrimitiveFigure::PrimitiveFigure(const PrimitiveFigure& object)
{
	m_Vertices = std::vector<Vertex>(object.m_Vertices.begin(), object.m_Vertices.end());
	m_Indices = std::vector<unsigned int>(object.m_Indices.begin(), object.m_Indices.end());
	m_Color = object.m_Color;
	Init();
}

PrimitiveFigure::~PrimitiveFigure()
{
	glDeleteVertexArrays(1, &m_VertexArray);
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteBuffers(1, &m_ElementBuffer);
}

void PrimitiveFigure::Init()
{
	glGenVertexArrays(1, &m_VertexArray);
	glGenBuffers(1, &m_VertexBuffer);
	glGenBuffers(1, &m_ElementBuffer);
	glBindVertexArray(m_VertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(int), &m_Indices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); //offset depends on Vertex
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
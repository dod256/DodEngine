#pragma once
#include "../precomp.h"
#include "IDrawable.h"
#include "Color.h"
#include "PrimitiveFigure.h"
#include "../Math/DVector.h"
#include "DVertex.h"

class DPolygon : public IDrawable
{
public:
	~DPolygon();
	DPolygon() {};
	DPolygon(std::vector<DVec4> vertices, Color color = Color(0.0f, 0.0f, 0.0f, 1.0f));
	DPolygon(const DPolygon& anotherArea);
	DPolygon(const std::vector<DVertex>& vertices);
	void Draw(const Shader& shader) const override;
	Color GetColor() { return m_Color; };
	void SetColor(Color newValue);
	void Init();
	const std::vector<DVertex>& GetVertices() const { return m_Vertices; };
private:
	Color m_Color;
	std::vector<DVec4> m_VerticesOld;
	PrimitiveFigure m_OpenGLArea;

	bool m_NewWay = false;
	std::vector<DVertex> m_Vertices;

//OpenGL Specific
	std::vector<DFloat> m_ViewportVertices;
	std::vector<DU32> m_Indices;
	DU32 m_VertexArray = 0;
	DU32 m_VertexBuffer = 0;
	DU32 m_ElementBuffer = 0;

//Texture
	DU32 m_Texture;


};


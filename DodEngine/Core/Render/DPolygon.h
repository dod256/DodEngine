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
	DPolygon(const DPolygon& polygon);
	DPolygon(const std::vector<DVertex>& vertices);
	void Draw(const Shader& shader) const override;
	void Init();
	void InitTexture(const char* fileName);
	const std::vector<DVertex>& GetVertices() const { return m_Vertices; };
	virtual void SetColor(Color color);
private:
	std::vector<DVertex> m_Vertices;

//OpenGL Specific
	std::vector<DFloat> m_ViewportVertices;
	std::vector<DU32> m_Indices;
	DU32 m_VertexArray = 0;
	DU32 m_VertexBuffer = 0;
	DU32 m_ElementBuffer = 0;

//Texture
	bool IsWithTexture = false;
	DU32 m_Texture = 0;


};


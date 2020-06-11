#pragma once
#include "../precomp.h"
#include "IDrawable.h"
#include "Color.h"
#include "../Math/DVector.h"
#include "DVertex.h"
#include "Renderable.h"

class DPolygon : public IDrawable
{
public:
	DPolygon() {};
	DPolygon(const DPolygon& polygon);
	DPolygon& operator=(const DPolygon& polygon);
	DPolygon(const std::vector<DVertex>& vertices);
	void Draw() const override;
	const std::vector<DVertex>& GetVertices() const { return m_Vertices; };
	virtual void SetColor(Color color);
private:
	std::vector<DVertex> m_Vertices;
	DU32 m_MeshID = 0;
};


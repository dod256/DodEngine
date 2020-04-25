#pragma once
#include "../precomp.h"
#include "IDrawable.h"
#include "Color.h"
#include "PrimitiveFigure.h"
#include "../Math/DVector.h"

class DArea : public IDrawable
{
public:
	DArea() {};
	DArea(std::vector<DVec4> vertices, Color color = Color(0.0f, 0.0f, 0.0f, 1.0f));
	DArea(const DArea& anotherArea);
	void Draw(const Shader& shader) const override;
	Color GetColor() { return m_Color; };
	void SetColor(Color newValue);
	void Init();
private:
	Color m_Color;	
	std::vector<DVec4> m_Vertices;
	PrimitiveFigure m_OpenGLArea;
};


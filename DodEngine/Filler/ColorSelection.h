#pragma once
#include "..\Core\IClickable.h"
#include "..\Core\Render\PrimitiveFigure.h"
#include "..\Core\Render\Vertex.h"
#include "..\Core\Render\Color.h"

class Field;

class ColorSelection : public IClickable, public PrimitiveFigure
{
public:
	ColorSelection(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Color color, Field* field);
	ColorSelection(const ColorSelection& button);
	void OnClick(float mouseXPos, float mouseYPos) const;
private:
	Field* m_Field;
};


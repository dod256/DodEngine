#pragma once
#include "..\Core\precomp.h"
#include "..\Core\IClickable.h"
#include "..\Core\Render\DPolygon.h"
#include <functional>


class ColorSelection : public IClickable, IDrawable
{
public:
	ColorSelection() {};
	ColorSelection(const std::vector<DVertex>& vertices, std::function<void(Color color)>& onClickFunc, Color color);
	void OnClick(float mouseXPos, float mouseYPos) const;
	void Draw() const override;
	void Init();
	void InitTexture(const char* fileName);
private:
	DPolygon m_Polygon;
	std::function<void(Color color)> m_OnClickFunc;
	Color m_Color;
};


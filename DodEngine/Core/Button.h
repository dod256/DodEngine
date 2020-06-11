#pragma once
#include "precomp.h"
#include "IClickable.h"
#include "Render\DPolygon.h"
#include <functional>


class Button : public IClickable, IDrawable
{
public:
	Button() {};
	Button(const std::vector<DVertex>& vertices, std::function<void()>& onClickFunc);
	void OnClick(float mouseXPos, float mouseYPos) const;
	void Draw() const override;
	void Init();
	void InitTexture(const char* fileName);
private:
	DPolygon m_Polygon;
	std::function<void()> m_OnClickFunc;
};


#pragma once

#include "precomp.h"
#include "IClickable.h"
#include "Render\DPolygon.h"
#include <functional>


class Button : public IClickable, IDrawable
{
public:
	Button() {};
	Button(std::vector<DVec4> vertices, Color color, std::function<void()> onClickFunc);
	Button(const std::vector<DVertex>& vertices, std::function<void()> onClickFunc);
	void OnClick(float mouseXPos, float mouseYPos) const;
	void Draw(const Shader& shader) const;
	void Init();
private:
	DPolygon m_Polygon;
	std::function<void()> m_OnClickFunc;
};


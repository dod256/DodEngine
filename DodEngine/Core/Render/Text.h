#pragma once
#include <string>
#include <functional>
#include "..\precomp.h"
#include "IDrawable.h"
#include "..\Math\DVector.h"
#include "..\IClickable.h"

class Text : public IDrawable, IClickable
{
public:
	Text(std::string text, DVec4 color, DFloat x = 0.0f, DFloat y = 0.0f, DFloat scale = 1.0f);
	void AddOnClick(std::function<void()>& onClickFunc);
	void OnClick(float mouseXPos, float mouseYPos) const;
	void Draw() const override;
private:
	std::string m_Text;
	DFloat m_X = 0.0f;
	DFloat m_Y = 0.0f;
	DFloat m_Scale = 1.0f;
	DVec4 m_Color;
	std::function<void()> m_OnClickFunc;
};


#pragma once
#include <vector>
#include "Shader.h"

 class IDrawable
{
public:
	virtual void Draw(const Shader& shader) const = 0;
};

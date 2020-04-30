#pragma once
#include "..\precomp.h"

class DPoint2
{
public:
	DPoint2() {};
	DPoint2(DFloat _x, DFloat _y) : x(_x), y(_y) {};

	DFloat x = 0.0f;
	DFloat y = 0.0f;

	bool operator < (const DPoint2& point) const;
	bool operator == (const DPoint2& point) const;
};


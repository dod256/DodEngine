#pragma once
#include "../precomp.h"
#include <vector>

class DVec4
{
public:
	DVec4();
	DVec4(std::vector<DFloat> values);
	DVec4(DFloat x1, DFloat x2, DFloat x3, DFloat x4);
	DVec4(const DVec4& vec4);
	DFloat& operator[] (int index);
private:
	static const DU32 DVEC4_SIZE = 4;
	DFloat m_Values[DVEC4_SIZE];
};
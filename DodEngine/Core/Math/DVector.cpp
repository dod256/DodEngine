#include "DVector.h"
#include <algorithm>

float& DVec4::operator[] (int index)
{
	return m_Values[index];
}

DVec4::DVec4()
{
	memset(m_Values, 0, sizeof(m_Values));
}

DVec4::DVec4(std::vector<DFloat> values)
{
	memset(m_Values, 0, sizeof(m_Values));
	DU32 sz = std::min((DU32) values.size(), DVEC4_SIZE);
	for(DU32 i = 0; i < sz; ++i)
	{
		m_Values[i] = values[i];
	}
}

DVec4::DVec4(const DVec4& vec4)
{
	memcpy(m_Values, vec4.m_Values, 4 * sizeof(DFloat));
}

DVec4::DVec4(DFloat x1, DFloat x2, DFloat x3, DFloat x4)
{
	m_Values[0] = x1;
	m_Values[1] = x2;
	m_Values[2] = x3;
	m_Values[3] = x4;
}
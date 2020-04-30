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
	DFloat& operator[] (int index) const;
private:
	static const DU32 DVEC4_SIZE = 4;
	mutable DFloat m_Values[DVEC4_SIZE];
};

class DVec2
{
public:
	DVec2();
	DVec2(std::vector<DFloat> values);
	DVec2(DFloat x1, DFloat x2);
	DVec2(const DVec2& vec2);
	DFloat& operator[] (int index) const;
private:
	static const DU32 DVEC2_SIZE = 2;
	mutable DFloat m_Values[DVEC2_SIZE];
};

class DVec3
{
public:
	DVec3();
	DVec3(std::vector<DFloat> values);
	DVec3(DFloat x1, DFloat x2, DFloat x3);
	DVec3(const DVec3& vec2);
	DFloat& operator[] (int index) const;
private:
	static const DU32 DVEC3_SIZE = 3;
	mutable DFloat m_Values[DVEC3_SIZE];
};
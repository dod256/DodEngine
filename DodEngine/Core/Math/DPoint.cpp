#include "DPoint.h"
#include <algorithm>

bool DPoint2::operator < (const DPoint2& point) const
{
	return x < point.x - EPS || std::abs(x - point.x) < EPS && y < point.y - EPS;
}

bool DPoint2::operator == (const DPoint2& point) const
{
	return std::abs(x - point.x) < EPS && std::abs(y - point.y) < EPS;
}
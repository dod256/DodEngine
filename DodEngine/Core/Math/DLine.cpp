#include "DLine.h"
#include <algorithm>
#include <cmath>

DLine::DLine(DPoint2 p, DPoint2 q)
{
	a = p.y - q.y;
	b = q.x - p.x;
	c = -a * p.x - b * p.y;
	Normalize();
}

void DLine::Normalize()
{
	DFloat z = std::sqrt(a * a + b * b);
	if (std::abs(z) > EPS)
	{
		a /= z;
		b /= z;
		c /= z;
	}
}

DFloat DLine::Distance(DPoint2 point) const
{
	return a * point.x + b * point.y + c;
}
#include "MathHelper.h"
#include <algorithm>

bool MathHelper::IsBetween(DFloat left, DFloat right, DFloat point)
{
	return std::min(left, right) <= point + EPS && point <= std::max(left, right) + EPS;
}

inline DFloat MathHelper::Det2d(DFloat a, DFloat b, DFloat c, DFloat d)
{
	return a * d - b * c;
}

DVec3 MathHelper::CreateLine(DVec2 p1, DVec2 p2)
{
	DVec3 line(0.0f, 0.0f, 0.0f);
	if (p1[0] == p2[0] && p1[1] == p2[1]) // not a line
	{
		return line;
	}
	if (p1[0] == p2[0]) // vertical line
	{
		line[0] = 1.0f;
		line[1] = 0.0f;
		line[2] = -p1[0];
		return line;
	}
	if (p1[1] == p2[1]) // vertical line
	{
		line[0] = 0.0f;
		line[1] = 1.0f;
		line[2] = -p1[1];
		return line;
	}
	line[0] = p2[1] - p1[1];
	line[1] = p1[0] - p2[0];
	line[2] = -p1[1] * line[1] - p1[0] * line[0];
	return line;
}

inline bool MathHelper::OnLine(DVec2 point, DVec3 line)
{
	return point[0] * line[0] + point[1] * line[1] + line[2] == 0;
}

bool MathHelper::OnSegment(DVec2 point, DVec2 seg1, DVec2 seg2)
{
	if (OnLine(point, CreateLine(seg1, seg2)))
	{
		if (std::min(seg1[0], seg2[0]) <= point[0] && point[0] <= std::max(seg1[0], seg2[0]) &&
			std::min(seg1[1], seg2[1]) <= point[1] && point[1] <= std::max(seg1[1], seg2[1]))
		{
			return true;
		}
	}
	return false;
}

inline DFloat MathHelper::Area(DVec2 a, DVec2 b, DVec2 c)
{
	return (b[0] - a[0]) * (c[1] - a[1]) - (b[1] - a[1]) * (c[0] - a[0]);
}

bool MathHelper::BoundingBooxCheck(DFloat a, DFloat b, DFloat c, DFloat d)
{
	if (a > b)
	{
		std::swap(a, b);
	}
	if (c > d)
	{
		std::swap(c, d);
	}
	return std::max(a, c) <= std::min(b, d) + EPS;
}

bool MathHelper::IsSegmentsIntersect(DVec2 a, DVec2 b, DVec2 c, DVec2 d)
{
	return BoundingBooxCheck(a[0], b[0], c[0], d[0])
		&& BoundingBooxCheck(a[1], b[1], c[1], d[1])
		&& Area(a, b, c) * Area(a, b, d) <= 0
		&& Area(c, d, a) * Area(c, d, b) <= 0;
}

bool MathHelper::Intersection(DPoint2 a, DPoint2 b, DPoint2 c, DPoint2 d, DPoint2& left, DPoint2& right)
{
	if (!BoundingBooxCheck(a.x, b.x, c.x, d.x) || !BoundingBooxCheck(a.y, b.y, c.y, d.y))
	{
		return false;
	}
	DLine m(a, b);
	DLine n(c, d);
	double zn = Det2d(m.a, m.b, n.a, n.b);
	if (abs(zn) < EPS)
	{
		if (abs(m.Distance(c)) > EPS || abs(n.Distance(a)) > EPS)
		{
			return false;
		}
		if (b < a)  std::swap(a, b);
		if (d < c)  std::swap(c, d);
		left = std::max(a, c);
		right = std::min(b, d);
		return true;
	}
	else {
		left.x = right.x = -Det2d(m.c, m.b, n.c, n.b) / zn;
		left.y = right.y = -Det2d(m.a, m.c, n.a, n.c) / zn;
		return IsBetween(a.x, b.x, left.x)
			&& IsBetween(a.y, b.y, left.y)
			&& IsBetween(c.x, d.x, left.x)
			&& IsBetween(c.y, d.y, left.y);
	}
}

bool MathHelper::IsInPolygon(DPoint2 p1, const std::vector<DPoint2> polygon)
{
	DU32 size = polygon.size();
	DPoint2 ray(INF, p1.y);
	DU32 count = 0;
	for (DU32 i = 0; i < polygon.size(); ++i)
	{
		DPoint2 left, right;
		if (Intersection(p1, ray, polygon[i], polygon[(i + 1) % size], left, right))
		{
			if (polygon[i] == left || polygon[i] == right)
			{
				if (polygon[(i + 1) % size].y >= p1.y)
				{
					continue;
				}
			}
			if (polygon[(i + 1) % size] == left || polygon[(i + 1) % size] == right)
			{
				if (polygon[i].y >= p1.y)
				{
					continue;
				}
			}
			++count;
		}
	}

	return count % 2;
}
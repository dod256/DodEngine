#pragma once
#include "..\precomp.h"
#include "DVector.h"
#include "DPoint.h"
#include "DLine.h"

class MathHelper
{
public:
	//On a line
	static inline bool IsBetween(DFloat left, DFloat right, DFloat point);
	//On a plane
	static inline DFloat Det2d(DFloat a, DFloat b, DFloat c, DFloat d);
	static DVec3 CreateLine(DVec2 p1, DVec2 p2);
	static inline bool OnLine(DVec2 point, DVec3 line);
	static bool OnSegment(DVec2 point, DVec2 seg1, DVec2 seg2);
	static inline DFloat Area(DVec2 a, DVec2 b, DVec2 c);	
	static bool BoundingBooxCheck(DFloat a, DFloat b, DFloat c, DFloat d);
	static inline bool IsSegmentsIntersect(DVec2 a, DVec2 b, DVec2 c, DVec2 d);
	static bool Intersection(DPoint2 a, DPoint2 b, DPoint2 c, DPoint2 d, DPoint2& left, DPoint2& right);
	static bool IsInPolygon(DPoint2 p1, const std::vector<DPoint2> polygon);
};


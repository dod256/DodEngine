#pragma once

#include "..\precomp.h"
#include "DPoint.h"

class DLine
{
public:
	DLine() {};
	DLine(DPoint2 p, DPoint2 q);
	void Normalize();
	DFloat Distance(DPoint2 point) const;
	DFloat a = 0.0f;
	DFloat b = 0.0f;
	DFloat c = 0.0f;
};


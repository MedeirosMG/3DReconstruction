#include "stdafx.h"
#include "PointPair.h"

namespace Entities {

	PointPair::PointPair(Point3f firstPoint, Point3f secondPoint) : FirstPoint(firstPoint), SecondPoint(secondPoint) {}

	PointPair::~PointPair()
	{
	}

}


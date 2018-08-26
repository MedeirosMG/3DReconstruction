#include "stdafx.h"
#include "CustomPoint.h"

namespace Entities {

	CustomPoint::CustomPoint(float x, float y, float z) : X(x), Y(y), Z(z) {}

	CustomPoint::CustomPoint() {}

	CustomPoint::~CustomPoint()
	{
	}

	// Return object Point3f, used by OpenCV
	Point3f CustomPoint::ReturnPoint3f()
	{
		return Point3f(X, Y, Z);
	}

	// Return list of Point3f conversion
	vector<Point3f> CustomPoint::ReturnPoint3f(vector<CustomPoint> points) 
	{
		vector<Point3f> _points;

		for each (CustomPoint point in points)
		{
			_points.push_back(Point3f(point.X, point.Y, point.Z));
		}

		return _points;
	}
}
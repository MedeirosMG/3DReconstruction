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

	// Add value to list of points and return new list
	vector<Point3f> CustomPoint::AddValueToPoints(vector<Point3f> points, float maxValue)
	{
		vector<Point3f> _points;

		for each (Point3f point in points)
		{
			_points.push_back(Point3f(point.x + maxValue, point.y + maxValue, point.z + maxValue));
		}

		return _points;
	}

	// Get max value with the coordinate using a vector points
	float CustomPoint::GetMaxAbsCoord(vector<Point3f> points, string coordinate)
	{
		float maxValue = 0.0;

		for each (Point3f point in points)
		{
			float numTemp = 0.0;
			if (coordinate == "x")
				numTemp = point.x;
			else if (coordinate == "y")
				numTemp = point.y;
			else if (coordinate == "z")
				numTemp = point.z;


			if (abs(numTemp) > maxValue)
				maxValue = abs(numTemp);
		}

		return maxValue;
	}
}
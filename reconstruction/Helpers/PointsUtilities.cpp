#include "stdafx.h"
#include "PointsUtilities.h"

namespace Utilities {
	PointUtilities::PointUtilities()
	{
		_openCv = new OpenCV();
	}

	PointUtilities::PointUtilities(OpenCV* openCv)
	{
		_openCv = openCv;
	}


	PointUtilities::~PointUtilities()
	{
	}

	// Return object Point3f, used by OpenCV
	Point3f PointUtilities::ReturnPoint3f(CustomPoint point)
	{
		return Point3f(point.X, point.Y, point.Z);
	}

	// Return list of Point3f conversion
	vector<Point3f> PointUtilities::ReturnPoint3f(vector<CustomPoint> points)
	{
		vector<Point3f> _points;

		for each (CustomPoint point in points)
		{
			_points.push_back(Point3f(point.X, point.Y, point.Z));
		}

		return _points;
	}

	// Add value to list of points and return new list
	vector<Point3f> PointUtilities::AddValueToPoints(vector<Point3f> points, float maxValue)
	{
		vector<Point3f> _points;

		for each (Point3f point in points)
		{
			_points.push_back(Point3f(point.x + maxValue, point.y + maxValue, point.z + maxValue));
		}

		return _points;
	}

	// Get max value with the coordinate using a vector points
	float PointUtilities::GetMaxAbsCoord(vector<Point3f> points, string coordinate)
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
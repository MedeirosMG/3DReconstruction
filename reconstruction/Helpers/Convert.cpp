#include "stdafx.h"
#include "Convert.h"

namespace Helpers {

	Convert::Convert()
	{
		_openCv = new OpenCV();
	}

	Convert::Convert(OpenCV* openCv)
	{
		_openCv = openCv;
	}


	Convert::~Convert()
	{
	}

	// Return object Point3f, used by OpenCV
	Point3f Convert::CustomPointTo3f(CustomPoint point)
	{
		return Point3f(point.X, point.Y, point.Z);
	}

	// Return list of Point3f conversion
	vector<Point3f> Convert::CustomPointTo3f(vector<CustomPoint> points)
	{
		vector<Point3f> _points;

		for each (CustomPoint point in points)
		{
			_points.push_back(CustomPointTo3f(point));
		}

		return _points;
	}

	// Return object Point2f, used by OpenCV
	Point2f Convert::CustomPointTo2f(CustomPoint point)
	{
		return Point2f(point.X, point.Y);
	}

	// Return list of Point2f conversion
	vector<Point2f> Convert::CustomPointTo2f(vector<CustomPoint> points)
	{
		vector<Point2f> _points;

		for each (CustomPoint point in points)
		{
			_points.push_back(CustomPointTo2f(point));
		}

		return _points;
	}
}
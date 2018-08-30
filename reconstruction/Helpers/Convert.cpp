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
	Point3f Convert::Point3fTo3f(Point3f point)
	{
		return Point3f(point.x, point.y, point.z);
	}

	// Return list of Point3f conversion
	vector<Point3f> Convert::Point3fTo3f(vector<Point3f> points)
	{
		vector<Point3f> _points;

		for each (Point3f point in points)
		{
			_points.push_back(Point3fTo3f(point));
		}

		return _points;
	}

	// Return object Point2f, used by OpenCV
	Point2f Convert::Point3fTo2f(Point3f point)
	{
		return Point2f(point.x, point.y);
	}

	// Return list of Point2f conversion
	vector<Point2f> Convert::Point3fTo2f(vector<Point3f> points)
	{
		vector<Point2f> _points;

		for each (Point3f point in points)
		{
			_points.push_back(Point3fTo2f(point));
		}

		return _points;
	}
}
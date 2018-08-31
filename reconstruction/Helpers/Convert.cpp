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

	vector<PointPair> Convert::DMatchToPointPair(vector<DMatch> matches, vector<KeyPoint> firstImageKeyPoints, vector<KeyPoint> secondImageKeyPoints) 
	{
		//Result of matches
		vector<PointPair> result;

		//Auxiliar Custom Points
		Point3f auxPoint1(0, 0, 0);
		Point3f auxPoint2(0, 0, 0);

		//Auxiliar PointPair
		PointPair auxPair(auxPoint1, auxPoint2);

		//Loop that build the point pair vector  
		for (int i = 0; i< matches.size(); i++) {

			//Calculations to keep points inside the resolution of the image
			auxPair.FirstPoint.x = firstImageKeyPoints[i].pt.x;
			auxPair.FirstPoint.y = firstImageKeyPoints[i].pt.y;
			auxPair.FirstPoint.z = 0;

			//Calculations to keep points inside the resolution of the image
			auxPair.SecondPoint.x = secondImageKeyPoints[matches[i].trainIdx].pt.x;
			auxPair.SecondPoint.y = secondImageKeyPoints[matches[i].trainIdx].pt.y;
			auxPair.SecondPoint.z = 0;

			//Simple filter by Y axis
			if (abs(auxPair.FirstPoint.y - auxPair.SecondPoint.y) > 0.2)
				continue;

			result.push_back(auxPair);
		}

		return result;
	}
}
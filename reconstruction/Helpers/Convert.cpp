#include "stdafx.h"
#include "Convert.h"

namespace Helpers {

	Convert::Convert()
	{
		_openCv = new OpenCV();
	}

	bool Convert::CheckInterval(float begin, float end, float val)
	{
		return (val >= begin && val <= end);
	}

	Convert::Convert(OpenCV* openCv)
	{
		_openCv = openCv;
	}


	Convert::~Convert()
	{
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

			result.push_back(auxPair);
		}

		return result;
	}

	vector<Vec<Point3f, 3>> Convert::Tiangles2dTo3d(vector<Vec6f> triangles, vector<Point3f> points)
	{
		vector<Vec<Point3f, 3>> result;
		float interval = 1.0;

		for each (Vec6f triangle in triangles)
		{
			Point2f pt1{ triangle[0], triangle[1] };
			Point2f pt2{ triangle[2], triangle[3] };
			Point2f pt3{ triangle[4], triangle[5] };

			Point3f pt13D, pt23D, pt33D;

			// Point 1
			for (int i = 0; i < points.size(); i++)
			{
				if (CheckInterval(points[i].x - interval, points[i].x + interval, pt1.x) && CheckInterval(points[i].y - interval, points[i].y + interval, pt1.y))
				{
					pt13D = Point3f(points[i].x, points[i].y, points[i].z);
					//points.erase(points.begin() + i, points.begin() + i);
					break;
				}
			}

			if (pt13D.x == 0 && pt13D.y == 0)
				pt13D = Point3f(pt1.x, pt1.y, 0);

			// Point 2
			for (int i = 0; i < points.size(); i++)
			{
				if (CheckInterval(points[i].x - interval, points[i].x + interval, pt2.x) && CheckInterval(points[i].y - interval, points[i].y + interval, pt2.y))
				{
					pt23D = Point3f(points[i].x, points[i].y, points[i].z);
					//points.erase(points.begin() + i, points.begin() + i);
					break;
				}
			}

			if (pt23D.x == 0 && pt23D.y == 0)
				pt23D = Point3f(pt2.x, pt2.y, 0);

			// Point 1
			for (int i = 0; i < points.size(); i++)
			{
				if (CheckInterval(points[i].x - interval, points[i].x + interval, pt3.x) && CheckInterval(points[i].y - interval, points[i].y + interval, pt3.y))
				{
					pt33D = Point3f(points[i].x, points[i].y, points[i].z);
					//points.erase(points.begin() + i, points.begin() + i);
					break;
				}
			}

			if (pt33D.x == 0 && pt33D.y == 0)
				pt33D = Point3f(pt3.x, pt3.y, 0);

			result.push_back(Vec<Point3f, 3>(pt13D, pt23D, pt33D));
		}

		return result;
	}
}
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
	vector<Point3f> PointUtilities::PointsTranslocate(vector<Point3f> points, float maxValue)
	{
		vector<Point3f> _points;

		for each (Point3f point in points)
		{
			_points.push_back(Point3f(point.x + maxValue, point.y + maxValue, point.z + maxValue));
		}

		return _points;
	}

	// Mult all point to apply zoom 
	vector<Point3f> PointUtilities::PointsZoom(vector<Point3f> points, int zoom)
	{
		vector<Point3f> _points;

		for each(Point3f point in points)
		{
			_points.push_back(Point3f(point.x * zoom, point.y * zoom, point.z * zoom));
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

	vector<CustomPoint> PointUtilities::GetMockPoints(string fileRead)
	{
		// Temps for reading file
		float _x = 0, _y = 0, _z = 0;
		string temp;
		ifstream InFile;

		InFile.open(fileRead);

		//Vector temp to return
		vector<CustomPoint> _return;

		while (!InFile.eof()) // To get you all the lines.
		{
			// Get the points 
			InFile >> _x;
			InFile >> _y;
			InFile >> _z;

			// Add in return
			_return.push_back(CustomPoint(_x * 100, _y * 100, _z * 100));
		}

		InFile.close();
		return _return;
	}

	float PointUtilities::GetMaxAbsCoord(vector<Vec6f> points) 
	{
		float maxValue = 0.0;

		for (size_t i = 0; i < points.size(); i++) {
			Vec6f triangle = points[i];
			Point pt1{ cvRound(triangle[0]), cvRound(triangle[1]) };
			Point pt2{ cvRound(triangle[2]), cvRound(triangle[3]) };
			Point pt3{ cvRound(triangle[4]), cvRound(triangle[5]) };

			if (abs(pt1.x) > maxValue)
				maxValue = abs(pt1.x);

			if (abs(pt1.y) > maxValue)
				maxValue = abs(pt1.y);

			if (abs(pt2.x) > maxValue)
				maxValue = abs(pt2.x);

			if (abs(pt2.y) > maxValue)
				maxValue = abs(pt2.y);

			if (abs(pt3.x) > maxValue)
				maxValue = abs(pt3.x);

			if (abs(pt3.y) > maxValue)
				maxValue = abs(pt3.y);
		}

		return maxValue;
	}
}
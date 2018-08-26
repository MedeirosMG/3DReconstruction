#include "stdafx.h"
#include "DelaunayService.h"

namespace Services {
	DelaunayService::DelaunayService(OpenCV* openCv)
	{
		_openCv = openCv;
	}
	DelaunayService::DelaunayService()
	{
		_openCv = new OpenCV();
	}


	DelaunayService::~DelaunayService()
	{
	}

	vector<CustomPoint> DelaunayService::MockPoints() 
	{
		// Temps for reading file
		float _x = 0, _y = 0, _z = 0;
		string temp;
		ifstream InFile;
		InFile.open(".\\Others Files\\MockPoints.obj");

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

	void DelaunayService::TestExecute()
	{
		vector<CustomPoint> points = MockPoints();

		//Convert Points
		CustomPoint *converter = new CustomPoint();
		vector<Point3f> _points = converter->ReturnPoint3f(points);

		// Get max width and max height of points
		// Get max width and max height of points
		float maxWidth = MaxAbsValue(_points, "x");
		float maxHeight = MaxAbsValue(_points, "y");
		float maxAbs = 0.0;

		if (maxWidth > maxHeight)
			maxAbs = maxWidth;
		else if (maxHeight > maxWidth)
			maxAbs = maxHeight;

		Mat image = cvCreateImage(cvSize(maxWidth + maxAbs, maxHeight + maxAbs), 8, 1);
		
		
		vector<Vec6f> triangleList = Execute(points);

		for (size_t i = 0; i < triangleList.size(); i++) {
			Vec6f triangle = triangleList[i];
			Point pt1{ cvRound(triangle[0]), cvRound(triangle[1]) };
			Point pt2{ cvRound(triangle[2]), cvRound(triangle[3]) };
			Point pt3{ cvRound(triangle[4]), cvRound(triangle[5]) };
			
			_openCv->DrawLine(image, pt1, pt2);
			_openCv->DrawLine(image, pt2, pt3);
			_openCv->DrawLine(image, pt3, pt1);
		}

		_openCv->SaveImage(".\\Others Files\\MockPoints.jpg",image);
	}

	float DelaunayService::MaxAbsValue(vector<Point3f> points, string coordinate)
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
			else
				throw exception("Coordenada não existe.");


			if (abs(numTemp) > maxValue)
				maxValue = abs(numTemp);
		}

		return maxValue;
	}

	vector<Point3f> DelaunayService::AddMaxValue(vector<Point3f> points, float maxValue) {
		vector<Point3f> _points;

		for each (Point3f point in points)
		{
			_points.push_back(Point3f(point.x + maxValue, point.y + maxValue, point.z + maxValue));
		}

		return _points;
	}

	vector<Vec6f> DelaunayService::Execute(vector<CustomPoint> points)
	{
		//Convert Points
		CustomPoint *converter = new CustomPoint();
		vector<Point3f> _points = converter->ReturnPoint3f(points);

		// Get max width and max height of points
		float maxWidth = MaxAbsValue(_points, "x");
		float maxHeight = MaxAbsValue(_points, "y");
		float maxAbs = 0.0;

		if (maxWidth > maxHeight)
			maxAbs = maxWidth;
		else if (maxHeight > maxWidth)
			maxAbs = maxHeight;

		// Update values of points
		_points = AddMaxValue(_points, maxAbs);

		// Rectangle to be used with Subdiv2D
		Rect rect(0, 0, MaxAbsValue(_points, "x") + 10, MaxAbsValue(_points, "y") + 10);

		// Create an instance of Subdiv2D
		Subdiv2D subdiv(rect);

		// Insert points into subdiv
		for each (Point3f point in _points)
		{
			subdiv.insert(Point2f(point.x, point.y));
		}

		// Get triangle list
		vector<Vec6f> triangleList;
		subdiv.getTriangleList(triangleList);

		return triangleList;
	}
}
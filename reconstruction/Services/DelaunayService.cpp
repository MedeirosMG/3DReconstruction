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

	void DelaunayService::TestExecute(vector<CustomPoint> points)
	{
		if(points.size() == 0)
			vector<CustomPoint> points = MockPoints();

		//Convert Points
		CustomPoint *converter = new CustomPoint();
		vector<Point3f> _points = converter->ReturnPoint3f(points);

		// Get max width and max height of points
		// Get max width and max height of points
		float maxWidth = converter->GetMaxAbsCoord(_points, "x");
		float maxHeight = converter->GetMaxAbsCoord(_points, "y");
		float maxAbs = 0.0;

		if (maxWidth > maxHeight)
			maxAbs = maxWidth;
		else if (maxHeight > maxWidth)
			maxAbs = maxHeight;

		Mat image = cvCreateImage(cvSize(maxWidth + maxAbs, maxHeight + maxAbs), 8, 1);
		
		
		vector<Vec6f> triangleList = Execute(points, 100);

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

	vector<Vec6f> DelaunayService::Execute(vector<CustomPoint> points, int zoom)
	{
		//Convert Points
		CustomPoint *converter = new CustomPoint();
		vector<Point3f> _points = converter->ReturnPoint3f(points);

		for (int i = 0; i < _points.size(); i++)
		{
			points[i].X *= zoom;
			points[i].Y *= zoom;
		}

		// Get max width and max height of points
		float maxWidth = converter->GetMaxAbsCoord(_points, "x");
		float maxHeight = converter->GetMaxAbsCoord(_points, "y");
		float maxAbs = 0.0;

		if (maxWidth > maxHeight)
			maxAbs = maxWidth;
		else if (maxHeight > maxWidth)
			maxAbs = maxHeight;

		// Update values of points
		_points = converter->AddValueToPoints(_points, maxAbs);

		// Rectangle to be used with Subdiv2D
		Rect rect(0, 0, converter->GetMaxAbsCoord(_points, "x") + 10, converter->GetMaxAbsCoord(_points, "y") + 10);

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
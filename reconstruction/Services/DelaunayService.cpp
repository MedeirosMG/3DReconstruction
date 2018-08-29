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

	void DelaunayService::TestExecute(vector<CustomPoint> points, int zoom)
	{
		PointUtilities *converter = new PointUtilities();

		if(points.size() == 0)
			vector<CustomPoint> points = converter->GetMockPoints();

		//Convert Points
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
		
		
		vector<Vec6f> triangleList = Execute(points, zoom);

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
		PointUtilities *converter = new PointUtilities();
		vector<Point3f> _points = converter->ReturnPoint3f(points);

		_points = converter->PointsZoom(_points, zoom);

		// Get max width and max height of points
		float maxWidth = converter->GetMaxAbsCoord(_points, "x");
		float maxHeight = converter->GetMaxAbsCoord(_points, "y");
		float maxAbs = 0.0;

		if (maxWidth > maxHeight)
			maxAbs = maxWidth;
		else if (maxHeight > maxWidth)
			maxAbs = maxHeight;

		// Update values of points
		_points = converter->PointsTranslocate(_points, maxAbs);

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
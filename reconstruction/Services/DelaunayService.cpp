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
		return vector<CustomPoint>();
	}

	void DelaunayService::TestExecute()
	{
		Mat image = _openCv->ReadImage("D:\\Medei\\Desktop\\imagens\\img.jpg");

		vector<CustomPoint> points;
		points.push_back(CustomPoint(1360, 6, 0));
		points.push_back(CustomPoint(1360, 760, 0));
		points.push_back(CustomPoint(6, 6, 0));
		points.push_back(CustomPoint(6, 760, 0));
		points.push_back(CustomPoint(570, 400, 0));
		points.push_back(CustomPoint(570, 400, 0));
		points.push_back(CustomPoint(400, 302, 0));
		points.push_back(CustomPoint(390, 2, 0));
		points.push_back(CustomPoint(1000, 76, 0));
		points.push_back(CustomPoint(998, 720, 0));
		points.push_back(CustomPoint(4, 387 , 0));

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

		_openCv->SaveImage("D:\\Medei\\Desktop\\imagens\\img_.jpg",image);
	}

	vector<Vec6f> DelaunayService::Execute(vector<CustomPoint> points)
	{
		//Convert Points
		CustomPoint *converter = new CustomPoint();
		vector<Point3f> _points = converter->ReturnPoint3f(points);

		// Get max width and max height of points
		float maxWidth = 0.0, maxHeight = 0.0;
		for each (Point3f point in _points)
		{
			if (point.x > maxWidth)
				maxWidth = point.x;

			if (point.y > maxHeight)
				maxHeight = point.y;
		}

		// Rectangle to be used with Subdiv2D
		Rect rect(0, 0, maxWidth + 5.0, maxHeight + 5.0);

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
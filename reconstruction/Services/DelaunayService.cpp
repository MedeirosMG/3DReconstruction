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

	void DelaunayService::TestExecute(vector<Point3f> points)
	{
		PointUtilities *converter = new PointUtilities();

		if(points.size() == 0)
			vector<Point3f> points = converter->GetMockPoints();

		// Get max width and max height of points
		// Get max width and max height of points
		float maxWidth = converter->GetMaxAbsCoord(points, "x");
		float maxHeight = converter->GetMaxAbsCoord(points, "y");
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

	bool DelaunayService::CheckRectangle(int coord, Vec6f triangle)
	{
		Point _pt1{ cvRound(triangle[0]), cvRound(triangle[1]) };
		Point _pt2{ cvRound(triangle[2]), cvRound(triangle[3]) };
		Point _pt3{ cvRound(triangle[4]), cvRound(triangle[5]) };

		if (coord == _pt1.x || coord == _pt1.y)
			return true;
		else if (coord == _pt2.x || coord == _pt2.y)
			return true;
		else if (coord == _pt3.x || coord == _pt3.y)
			return true;
		else
			return false;
	}

	vector<Vec6f> DelaunayService::RemoveRectangle(vector<Vec6f> triangles) 
	{
		vector<Vec6f> retorno;
		PointUtilities *utilitie = new PointUtilities();
		Vec6f _triangle = triangles[1];

		Mat image = imread(".\\Others Files\\cabeca_1.png", CV_8UC3);
		vector<Vec4i> hierarchy;
		vector<vector<Point> > contours;
		findContours(image, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

		for (size_t i = 0; i < triangles.size(); i++) {
			Vec6f triangle = triangles[i];
			Point pt1{ cvRound(triangle[0]), cvRound(triangle[1]) };
			Point pt2{ cvRound(triangle[2]), cvRound(triangle[3]) };
			Point pt3{ cvRound(triangle[4]), cvRound(triangle[5]) };
			
			
			for (int j = 0; j < contours.size(); j++) {
				if (pointPolygonTest(contours[j], utilitie->GetMiddlePoint(Point2f(pt1.x, pt1.y), Point2f(pt2.x, pt2.y)), false) < 0)
					continue;
				else if (pointPolygonTest(contours[j], utilitie->GetMiddlePoint(Point2f(pt2.x, pt2.y), Point2f(pt3.x, pt3.y)), false) < 0)
					continue;
				else if (pointPolygonTest(contours[j], utilitie->GetMiddlePoint(Point2f(pt3.x, pt3.y), Point2f(pt1.x, pt1.y)), false) < 0)
					continue;
				else
					retorno.push_back(triangle);
			}
			
			/*
			if (CheckRectangle(pt1.x, _triangle) || CheckRectangle(pt1.y, _triangle))
				continue;
			else if (CheckRectangle(pt2.x, _triangle) || CheckRectangle(pt2.y, _triangle))
				continue;
			else if (CheckRectangle(pt3.x, _triangle) || CheckRectangle(pt3.y, _triangle))
				continue;
			else
				retorno.push_back(triangle);*/

			//retorno.push_back(triangle);
		}

		return retorno;
	}

	vector<Vec6f> DelaunayService::Execute(vector<Point3f> points)
	{
		//Convert Points
		PointUtilities *converter = new PointUtilities();

		// Get max width and max height of points
		float maxWidth = converter->GetMaxAbsCoord(points, "x");
		float maxHeight = converter->GetMaxAbsCoord(points, "y");
		float maxAbs = 0.0;

		if (maxWidth > maxHeight)
			maxAbs = maxWidth;
		else if (maxHeight > maxWidth)
			maxAbs = maxHeight;

		// Update values of points
		points = converter->PointsTranslocate(points, maxAbs);

		// Rectangle to be used with Subdiv2D
		Rect rect(0, 0, converter->GetMaxAbsCoord(points, "x") + 10, converter->GetMaxAbsCoord(points, "y") + 10);

		// Create an instance of Subdiv2D
		Subdiv2D subdiv(rect);

		// Insert points into subdiv
		for each (Point3f point in points)
		{
			subdiv.insert(Point2f(point.x, point.y));
		}

		// Get triangle list
		vector<Vec6f> triangleList;
		subdiv.getTriangleList(triangleList);

		//Return points in triangle to original value
		triangleList = converter->PointsTranslocate(triangleList, -maxAbs);

		return RemoveRectangle(triangleList);
	}
}
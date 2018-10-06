#include "stdafx.h"
#include "DelaunayService.h"
#include <iterator>
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
		
		
		vector<Vec6f> triangleList = Execute(points, points, Mat());

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

	bool DelaunayService::CheckInsidePoint(Point2f point, Mat contour)
	{
		int width = REC_SCREEN_DEFAULT_WIDTH;
		int height = REC_SCREEN_DEFAULT_HEIGHT;
		bool controlVariable = true;

		// Go to max width
		Point2f variablePoint = point;
		while (variablePoint.x < width)
		{
			if (contour.at<uchar>(variablePoint.y, variablePoint.x) != 0)
			{
				controlVariable = true;
				break;
			}
			else
			{ 
				controlVariable = false;
				variablePoint.x++;
			}
		}

		if (!controlVariable)
			return false;


		// Go to min width
		variablePoint = point;
		while (variablePoint.x > 0)
		{
			if (contour.at<uchar>(variablePoint.y, variablePoint.x) != 0)
			{
				controlVariable = true;
				break;
			}
			else
			{
				controlVariable = false;
				variablePoint.x--;
			}
		}

		if (!controlVariable)
			return false;

		// Go to max height
		variablePoint = point;
		while (variablePoint.y < height)
		{
			if (contour.at<uchar>(variablePoint.y, variablePoint.x) != 0)
			{
				controlVariable = true;
				break;
			}
			else
			{
				controlVariable = false;
				variablePoint.y++;
			}
		}

		if (!controlVariable)
			return false;


		// Go to min width
		variablePoint = point;
		while (variablePoint.y > 0)
		{
			if (contour.at<uchar>(variablePoint.y, variablePoint.x) != 0)
			{
				controlVariable = true;
				break;
			}
			else
			{
				controlVariable = false;
				variablePoint.y--;
			}
		}

		return controlVariable;
	}

	vector<Vec6f> DelaunayService::FilterTriangles(vector<Vec6f> triangles, Mat contour, Size screenSize)
	{
		PointUtilities *utilities = new PointUtilities();
		vector<Vec6f> result;		
		Point2f middlePoint;

		for (size_t i = 0; i < triangles.size(); i++) {
			Vec6f triangle = triangles[i];
			
			Point3f pt1 = utilities->CoordenateToPixel(Point3f(cvRound(triangle[0]), cvRound(triangle[1]), 0), screenSize);
			Point3f pt2 = utilities->CoordenateToPixel(Point3f(cvRound(triangle[2]), cvRound(triangle[3]), 0), screenSize);
			Point3f pt3 = utilities->CoordenateToPixel(Point3f(cvRound(triangle[4]), cvRound(triangle[5]), 0), screenSize);

			middlePoint = utilities->GetMiddlePoint(Point2f(pt1.x, pt1.y), Point2f(pt2.x, pt2.y));
			middlePoint.x = cvRound(middlePoint.x);
			middlePoint.y = cvRound(middlePoint.y);
			if (!CheckInsidePoint(middlePoint, contour))
				continue;

			middlePoint = utilities->GetMiddlePoint(Point2f(pt2.x, pt2.y), Point2f(pt3.x, pt3.y));
			middlePoint.x = cvRound(middlePoint.x);
			middlePoint.y = cvRound(middlePoint.y);
			if (!CheckInsidePoint(middlePoint, contour))
				continue;

			middlePoint = utilities->GetMiddlePoint(Point2f(pt3.x, pt3.y), Point2f(pt1.x, pt1.y));
			middlePoint.x = cvRound(middlePoint.x);
			middlePoint.y = cvRound(middlePoint.y);
			if (!CheckInsidePoint(middlePoint, contour))
				continue;

			result.push_back(triangle);
		}

		return result;
	}

	vector<Vec6f> DelaunayService::RemoveRectangle(vector<Vec6f> triangles) 
	{
		vector<Vec6f> retorno;
		PointUtilities *utilitie = new PointUtilities();
		Vec6f _triangle = triangles[1];

		for (size_t i = 0; i < triangles.size(); i++) {
			Vec6f triangle = triangles[i];
			Point pt1{ cvRound(triangle[0]), cvRound(triangle[1]) };
			Point pt2{ cvRound(triangle[2]), cvRound(triangle[3]) };
			Point pt3{ cvRound(triangle[4]), cvRound(triangle[5]) };

			if (CheckRectangle(pt1.x, _triangle) || CheckRectangle(pt1.y, _triangle))
				continue;
			else if (CheckRectangle(pt2.x, _triangle) || CheckRectangle(pt2.y, _triangle))
				continue;
			else if (CheckRectangle(pt3.x, _triangle) || CheckRectangle(pt3.y, _triangle))
				continue;
			else
				retorno.push_back(triangle);
		}

		return retorno;
	}

	vector<Vec6f> DelaunayService::Execute(vector<Point3f> pointsCalibration, vector<Point3f> contour, Mat contourDilated, Size sizeImg)
	{
		//Convert Points
		PointUtilities *converter = new PointUtilities();

		//Merge points
		vector<Point3f> points = converter->MergePoints(pointsCalibration, converter->PixelToCoordenate(contour, sizeImg));
		//vector<Point3f> points = pointsCalibration;
		std::ofstream outFile("points.txt");
		// the important part
		for (const auto &e : points) outFile << e.x<< " "<< e.y<<" "<<e.z << "\n";
		

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

		return FilterTriangles(RemoveRectangle(triangleList), contourDilated, sizeImg);
	}
}
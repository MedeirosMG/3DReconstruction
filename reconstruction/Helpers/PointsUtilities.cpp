#include "stdafx.h"
#include "PointsUtilities.h"

namespace Helpers {

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

	// Add value to list of points and return new list
	vector<Vec6f> PointUtilities::PointsTranslocate(vector<Vec6f> triangles, float maxValue)
	{
		vector<Vec6f> _triangles;

		for (size_t i = 0; i < triangles.size(); i++) {
			Vec6f triangle = triangles[i];
			Point pt1{ cvRound(triangle[0]), cvRound(triangle[1]) };
			Point pt2{ cvRound(triangle[2]), cvRound(triangle[3]) };
			Point pt3{ cvRound(triangle[4]), cvRound(triangle[5]) };

			_triangles.push_back(Vec6f(triangle[0] + maxValue,
										triangle[1] + maxValue,
										triangle[2] + maxValue,
										triangle[3] + maxValue,
										triangle[4] + maxValue,
										triangle[5] + maxValue));
		}

		return _triangles;
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

	vector<Point3f> PointUtilities::GetMockPoints(string fileRead)
	{
		// Temps for reading file
		float _x = 0, _y = 0, _z = 0;
		string temp;
		ifstream InFile;

		InFile.open(fileRead);

		//Vector temp to return
		vector<Point3f> _return;

		while (!InFile.eof()) // To get you all the lines.
		{
			// Get the points 
			InFile >> _x;
			InFile >> _y;
			InFile >> _z;

			// Add in return
			_return.push_back(Point3f(_x * 100, _y * 100, _z * 100));
		}

		InFile.close();
		return _return;
	}

	Point2f PointUtilities::GetMiddlePoint(Point2f pt1, Point2f pt2)
	{
		Point2f point;

		point.x = (pt1.x + pt2.x) / 2;
		point.y = (pt1.y + pt2.y) / 2;

		return point;
	}

	vector<Point3f> PointUtilities::MergePoints(vector<Point3f> pts1, vector<Point3f> pts2)
	{
		vector<Point3f> _return;

		_return.reserve(pts1.size() + pts2.size());
		_return.insert(_return.end(), pts1.begin(), pts1.end());
		_return.insert(_return.end(), pts2.begin(), pts2.end());
	
		return _return;
	}

	vector<Point3f> PointUtilities::PixelToCoordenate(vector<Point3f> points, Size screenSize)
	{
		vector<Point3f> pointsReturn;

		for each (Point3f point in points)
		{
			Point3f pt = PixelToCoordenate(point, screenSize);
			pointsReturn.push_back(pt);
		}

		return pointsReturn;
	}

	vector<PointPair> PointUtilities::PixelToCoordenate(vector<PointPair> points, Size screenSize)
	{
		vector<PointPair> pointsReturn;

		for each (PointPair point in points)
		{
			PointPair pt = PointPair(PixelToCoordenate(point.FirstPoint, screenSize), PixelToCoordenate(point.SecondPoint, screenSize));
			pointsReturn.push_back(pt);
		}

		return pointsReturn;
	}

	double PointUtilities::GetArea(vector<Point> points)
	{
		// (X[i], Y[i]) are coordinates of i'th point.		
		// Initialze area
		double area = 0.0;

		// Calculate value of shoelace formula
		int j = points.size() - 1;
		for (int i = 0; i < points.size(); i++)
		{
			area += (points[j].x + points[i].x) * (points[j].y - points[i].y);
			j = i;  // j is previous vertex to i
		}

		// Return absolute value
		return abs(area / 2.0);
	}

	Point3f PointUtilities::PixelToCoordenate(Point3f point, Size screenSize)
	{
		Point3f pt = Point3f((point.x - screenSize.width/2), (-point.y + screenSize.height/2), point.z);
		return pt;
	}

	Point3f PointUtilities::CoordenateToPixel(Point3f point, Size screenSize)
	{
		Point3f pt = Point3f(point.x + screenSize.width/2, screenSize.height/2 - point.y , point.z);
		return pt;
	}

	float PointUtilities::GetMaxAbsCoord(vector<Vec<Point3f, 3>> points)
	{
		float maxValue = 0.0;

		for each (Vec<Point3f, 3> item in points)
		{
			if (item[0].x > maxValue)
				maxValue = item[0].x;
			
			if (item[0].y > maxValue)
				maxValue = item[0].y;

			if (item[1].x > maxValue)
				maxValue = item[1].x;

			if (item[1].y > maxValue)
				maxValue = item[1].y;

			if (item[2].x > maxValue)
				maxValue = item[2].x;

			if (item[2].y > maxValue)
				maxValue = item[2].y;
		}

		return maxValue;
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

	void PointUtilities::FillUnstructuredGrid(vtkUnstructuredGrid * unstructuredGrid, vector<Point3f> pointsToApply)
	{
		vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
		vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();

		points->SetDataType(VTK_DOUBLE);
		cells->InsertNextCell(pointsToApply.size());
		for each (Point3f point in pointsToApply)
		{
			double newPoint[3] = { point.x, point.y, point.z >= 0 ? point.z : 0 };

			cells->InsertCellPoint(points->InsertNextPoint(newPoint));
		}

		points->Squeeze();
		unstructuredGrid->SetPoints(points);
		cells->Squeeze();
		unstructuredGrid->SetCells(VTK_VERTEX, cells);
	}
}
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
		/*
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

		_openCv->SaveImage(".\\Others Files\\MockPoints.jpg",image);*/
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

	void DelaunayService::FillUnstructuredGrid(vtkUnstructuredGrid * unstructuredGrid, vector<Point3f> pointsToApply)
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

	vector<Vec<Point3f, 3>> DelaunayService::GetTriangles(vtkUnstructuredGrid * unstructuredGrid)
	{
		vector<Vec<Point3f, 3>> result;

		for (vtkIdType i = 0; i < unstructuredGrid->GetNumberOfCells(); i++)
		{
			vtkCell* cell = unstructuredGrid->GetCell(i);
			double p0[3];
			double p1[3];
			double p2[3];

			cell->GetPoints()->GetPoint(0, p0);
			cell->GetPoints()->GetPoint(1, p1);
			cell->GetPoints()->GetPoint(2, p2);

			Vec<Point3f, 3> point = Vec<Point3f, 3>(Point3f(p0[0], p0[1], p0[2]), Point3f(p1[0], p1[1], p1[2]), Point3f(p2[0], p2[1], p2[2]));
			result.push_back(point);
		}

		return result;
	}

	bool DelaunayService::CheckInsidePoint(Point2f point, Mat contour)
	{
		int width = REC_SCREEN_DEFAULT_WIDTH;
		int height = REC_SCREEN_DEFAULT_HEIGHT;
		bool controlVariable = true;

		if (point.x > width || point.y > height)
			return false;

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

	vector<Vec<Point3f, 3>> DelaunayService::FilterTriangles(vector<Vec<Point3f, 3>> triangles, Mat contour, Size screenSize)
	{
		PointUtilities *utilities = new PointUtilities();
		vector<Vec<Point3f, 3>> result;
		Point2f middlePoint;

		OpenCV *open = new OpenCV();
		Mat mat1 = Mat(contour.rows, contour.cols, CV_8UC3);
		Mat mat2 = Mat(contour.rows, contour.cols, CV_8UC3);

		for each (Vec<Point3f, 3> triangle in triangles)
		{
			Point3f pt1 = triangle[0];
			Point3f pt2 = triangle[1];
			Point3f pt3 = triangle[2];

			open->DrawLine(mat1, Point(1, 1), Point(2, 2));
			open->DrawLine(mat1, Point(pt1.x, pt1.y), Point(pt2.x, pt2.y));
			open->DrawLine(mat1, Point(pt2.x, pt2.y), Point(pt3.x, pt3.y));
			open->DrawLine(mat1, Point(pt3.x, pt3.y), Point(pt1.x, pt1.y));

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


			open->DrawLine(mat2, Point(pt1.x, pt1.y), Point(pt2.x, pt2.y));
			open->DrawLine(mat2, Point(pt2.x, pt2.y), Point(pt3.x, pt3.y));
			open->DrawLine(mat2, Point(pt3.x, pt3.y), Point(pt1.x, pt1.y));
			result.push_back(triangle);
		}

		
		open->NewWindow("antes");
		open->NewWindow("depois");

		open->ShowImage(mat1, "antes");
		open->ShowImage(mat2, "depois");

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

	vector<Vec<Point3f, 3>> DelaunayService::Execute(vector<Point3f> pointsCalibration, vector<Point3f> contour, Mat contourDilated, Size sizeImg)
	{	
		PointUtilities *utilitie = new PointUtilities();
		vector<Vec<Point3f, 3>> triangleList;

		vtkSmartPointer<vtkUnstructuredGrid> inputUnstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
		FillUnstructuredGrid(inputUnstructuredGrid, utilitie->MergePoints(contour, pointsCalibration));		

		vtkSmartPointer<vtkDelaunay3D> delaunay3D = vtkSmartPointer<vtkDelaunay3D>::New();
		delaunay3D->SetInputData(inputUnstructuredGrid);
		delaunay3D->Update();

		vtkSmartPointer<vtkUnstructuredGrid> outputUnstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
		outputUnstructuredGrid = delaunay3D->GetOutput();

		triangleList = GetTriangles(outputUnstructuredGrid);

		return FilterTriangles(triangleList, contourDilated, sizeImg);
		
	}
}
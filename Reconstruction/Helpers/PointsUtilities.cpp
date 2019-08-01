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
	float PointUtilities::GetMaxAbsCoord(vector<Point3f> points, string coordinate, bool excludeZero)
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


			if (abs(numTemp) > maxValue && !isinf(numTemp)) {
				if (excludeZero && abs(numTemp) == 0)
					continue;

				maxValue = abs(numTemp);
			}
		}

		return maxValue;
	}

	float PointUtilities::GetMinAbsCoord(vector<Point3f> points, string coordinate, bool excludeZero)
	{
		float minValue = 9999999999;

		for each (Point3f point in points)
		{
			float numTemp = 0.0;

			if (coordinate == "x")
				numTemp = point.x;
			else if (coordinate == "y")
				numTemp = point.y;
			else if (coordinate == "z")
				numTemp = point.z;


			if (abs(numTemp) < minValue && !isinf(numTemp)) {
				if (excludeZero && abs(numTemp) == 0)
					continue;

				minValue = abs(numTemp);
			}
		}

		return minValue;
	}

	// Get max value with the coordinate using a vector points
	float PointUtilities::GetMaxAbsCoord(vector<vector<Point3f>> points, string coordinate, bool excludeZero)
	{
		float maxValue = 0.0;

		for each (vector<Point3f> row in points)
		{
			for each (Point3f point in  row)
			{
				float numTemp = 0.0;

				if (coordinate == "x")
					numTemp = point.x;
				else if (coordinate == "y")
					numTemp = point.y;
				else if (coordinate == "z")
					numTemp = point.z;


				if (abs(numTemp) > maxValue && !isinf(numTemp)) {
					if (excludeZero && abs(numTemp) == 0)
						continue;

					maxValue = abs(numTemp);
				}
			}
		}

		return maxValue;
	}

	float PointUtilities::GetMinAbsCoord(vector<vector<Point3f>> points, string coordinate, bool excludeZero)
	{
		float minValue = 9999999999;

		for each (vector<Point3f> row in points)
		{
			for each (Point3f point in  row)
			{
				float numTemp = 0.0;

				if (coordinate == "x")
					numTemp = point.x;
				else if (coordinate == "y")
					numTemp = point.y;
				else if (coordinate == "z")
					numTemp = point.z;


				if (abs(numTemp) < minValue && !isinf(numTemp)) {
					if (excludeZero && abs(numTemp) == 0)
						continue;

					minValue = abs(numTemp);
				}
			}
		}

		return minValue;
	}


	float PointUtilities::GetMaxAbsCoord(vector<float> points, bool excludeZero) {
		float maxValue = 0.0;

		for each (float point in points)
		{
			if (abs(point) > maxValue && !isinf(point)) {
				if (excludeZero && abs(point) == 0)
					continue;

				maxValue = abs(point);
			}
		}

		return maxValue;
	}

	float PointUtilities::GetMinAbsCoord(vector<float> points, bool excludeZero) {
		float minValue = 9999999999;

		for each (float point in points)
		{
			if (abs(point) < minValue && !isinf(point)) {
				if (excludeZero && abs(point) == 0)
					continue;

				minValue = abs(point);
			}
		}

		return minValue;
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

			if (item[0].z > maxValue)
				maxValue = item[0].z;

			if (item[1].x > maxValue)
				maxValue = item[1].x;

			if (item[1].y > maxValue)
				maxValue = item[1].y;

			if (item[1].z > maxValue)
				maxValue = item[1].z;

			if (item[2].x > maxValue)
				maxValue = item[2].x;

			if (item[2].y > maxValue)
				maxValue = item[2].y;

			if (item[2].z > maxValue)
				maxValue = item[2].z;
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

	// Get max value with the coordinate using a vector points
	float PointUtilities::GetMaxAbsCoord(Mat image, string coordinate, CameraProperties calib, bool excludeZero)
	{
		vector<Point3f> pointsMap;
		for (int j = 0; j < image.rows; j++)
		{
			for (int i = 0; i < image.cols; i++)
			{
				float zPoint = image.at<float>(j, i);
				//zPoint = calib.B *(calib.f / (zPoint + calib.doffs));
				pointsMap.push_back(Point3f(i, j, zPoint));
			}
		}

		return GetMaxAbsCoord(pointsMap, coordinate);
	}

	float PointUtilities::GetMinAbsCoord(Mat image, string coordinate, CameraProperties calib, bool excludeZero)
	{
		vector<Point3f> pointsMap;
		for (int j = 0; j < image.rows; j++)
		{
			for (int i = 0; i < image.cols; i++)
			{
				float zPoint = image.at<float>(j, i);
				//zPoint = calib.B *(calib.f / (zPoint + calib.doffs));
				//if (zPoint != 0)
					pointsMap.push_back(Point3f(i, j, zPoint));
			}
		}

		return GetMinAbsCoord(pointsMap, coordinate);
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

	vector<PointPair> PointUtilities::MergePoints(vector<PointPair> pts1, vector<PointPair> pts2)
	{
		vector<PointPair> _return;

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

	SiftResult PointUtilities::FilterKeyPoints(SiftResult result, int filterY, int filterDist, Mat img1, Mat img2)
	{
		//Filtro de pontos
		vector<DMatch> good_matches;
		
		double max_dist = 0, min_dist = 100;

		//-- Quick calculation of max and min distances between keypoints
		for (int i = 0; i < result.Matches.size(); i++)
		{
			double dist = result.Matches[i].distance;
			if (dist < min_dist) min_dist = dist;
			if (dist > max_dist) max_dist = dist;
		}

		printf("-- Max dist : %f \n", max_dist);
		printf("-- Min dist : %f \n", min_dist);


		/*for (int i = 0; i < result.Matches.size(); i++) {
			if (abs(result.FirstImageKeyPoints[result.Matches[i].queryIdx].pt.y - result.SecondImageKeyPoints[result.Matches[i].trainIdx].pt.y) <= filterY){
				// && result.Matches[i].distance < filterDist * min_dist) {
					good_matches.push_back(result.Matches[i]);
			}
		}*/
		
		vector<Point2f> points1;
		vector<Point2f> points2;

		for (int i = 0; i < result.Matches.size(); i++) {
			points1.push_back(result.FirstImageKeyPoints[result.Matches[i].queryIdx].pt);
			points2.push_back(result.SecondImageKeyPoints[result.Matches[i].trainIdx].pt);
				
		}

		
		Mat mask;
		Mat H = findHomography(points1, points2, CV_RANSAC, 5, mask);
		//cout << mask.type() << endl;
		for (int i = 0; i < mask.rows; i++) {
			//cout << (unsigned int)mask.at<uchar>(i) << endl;
			if ((unsigned int)mask.at<uchar>(i)) {
				good_matches.push_back(result.Matches[i]);
			}
		}

		SiftResult ret = result;
		ret.Matches = good_matches;
		drawMatches(img1, result.FirstImageKeyPoints, img2, result.SecondImageKeyPoints, good_matches, result.siftImg, Scalar::all(-1), Scalar::all(-1),
			vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
		return ret;
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
		Point3f pt = Point3f((point.x - screenSize.width / 2), (-point.y + screenSize.height / 2), point.z);
		return pt;
	}

	Point3f PointUtilities::CoordenateToPixel(Point3f point, Size screenSize)
	{
		Point3f pt = Point3f(point.x + screenSize.width / 2, screenSize.height / 2 - point.y, point.z);
		return pt;
	}

	

	void PointUtilities::FillUnstructuredGrid(vtkUnstructuredGrid * unstructuredGrid, vector<Point3f> pointsToApply)
	{
		vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
		vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();

		points->SetDataType(VTK_DOUBLE);
		cells->InsertNextCell(pointsToApply.size());
		for each (Point3f point in pointsToApply)
		{
			double newPoint[3] = { point.x, point.y, point.z };

			cells->InsertCellPoint(points->InsertNextPoint(newPoint));
		}

		points->Squeeze();
		unstructuredGrid->SetPoints(points);
		cells->Squeeze();
		unstructuredGrid->SetCells(VTK_VERTEX, cells);
	}

	void PointUtilities::FillUnstructuredGrid2(vtkUnstructuredGrid * unstructuredGrid, vector<Vec<Point3f, 4>> triangles)
	{
		vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
		vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();

		points->SetDataType(VTK_DOUBLE);
		for (int i = 0; i < triangles.size(); i++) {

			cells->InsertNextCell(4);
			double newPoint1[3] = { triangles[i][0].x, triangles[i][0].y, triangles[i][0].z };
			double newPoint2[3] = { triangles[i][1].x, triangles[i][1].y, triangles[i][1].z };
			double newPoint3[3] = { triangles[i][2].x, triangles[i][2].y, triangles[i][2].z };
			double newPoint4[3] = { triangles[i][3].x, triangles[i][3].y, triangles[i][3].z };

			cells->InsertCellPoint(points->InsertNextPoint(newPoint1));
			cells->InsertCellPoint(points->InsertNextPoint(newPoint2));
			cells->InsertCellPoint(points->InsertNextPoint(newPoint3));
			cells->InsertCellPoint(points->InsertNextPoint(newPoint4));
		}

		points->Squeeze();
		unstructuredGrid->SetPoints(points);
		cells->Squeeze();
		unstructuredGrid->SetCells(VTK_TETRA, cells);
	}

	bool PointUtilities::CheckInsidePoint(Point2f point, Mat contour)
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
}
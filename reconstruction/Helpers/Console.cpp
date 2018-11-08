#include "stdafx.h"
#include "Console.h"

namespace Helpers {

	// -------- Private

	string Console::PrintString(Point2f point)
	{
		return "P(" + to_string(point.x) + "," + to_string(point.y) + ")";
	}

	void Console::Pause() {
		cout << ">> Press any key to continue..." << endl;
		system("pause");
	}

	// -------- Public

	Console::Console()
	{

	}

	Console::~Console()
	{
	}

	void Console::Print(vector<Point3f> points, bool pause)
	{
		cout << "========================== Result vector<Point3f> ==============================" << endl;
		cout << ">> Size: " << points.size() << endl;

		int count = 1;
		for each (Point3f item in points)
		{
			if (count < 10)
				cout << "P[0" << count << "] = { " << item.x << " ; " << item.y << " ; " << item.z << " } " << endl;
			else
				cout << "P[" << count << "] = { " << item.x << " ; " << item.y << " ; " << item.z << " } " << endl;
			count++;

			if (count == 100)
				break;
		}

		cout << "=============================== Only top 100 ===================================" << endl << endl;

		if (pause)
			Pause();
	}

	void Console::Print(Point3f point, bool pause)
	{
		cout << "Point3f = { " << point.x << " ; " << point.y << " ; " << point.z << " } " << endl;

		if (pause)
			Pause();
	}

	void Console::Print(vector<Point2f> points, bool pause)
	{
		cout << "============================= Result vector<Point2f> =============================" << endl;
		cout << ">> Size: " << points.size() << endl;

		for (int i = 0; i < points.size(); i++) {

			if (i < 10)
				cout << "P[0" << i << "] = { " << points[i].x << " ; " << points[i].y << " } " << endl;
			else
				cout << "P[" << i << "] = { " << points[i].x << " ; " << points[i].y << " } " << endl;

			if (i == 99)
				break;
		}

		cout << "=============================== Only top 100 ===================================" << endl << endl;

		if (pause)
			Pause();
	}

	void Console::Print(Point2f point, bool pause)
	{
		cout << "Point2f = { " << point.x << " ; " << point.y << " } " << endl;

		if (pause)
			Pause();
	}

	void Console::Print(vector<vector<Point>> points, bool pause) {
		cout << "========================= Result vector<vector<Point>> =========================" << endl << endl;
		cout << ">> Size: " << points.size() << endl;

		for (int i = 0; i < points.size(); i++) {
			cout << " >>> Vector [0" << i << "]: " << endl;
			Print(points[i]);

			if (i == 99)
				break;
		}

		cout << "=================================== Only top 100 ===============================" << endl << endl;

		if (pause)
			system("pause");
	}

	void Console::Print(vector<Point> points, bool pause) {
		cout << "=============================== Result vector<Point> ===========================" << endl << endl;
		cout << ">> Size: " << points.size() << endl;

		for (int i = 0; i < points.size(); i++) {

			if (i < 10)
				cout << "P[0" << i << "] = { " << points[i].x << " ; " << points[i].y << " } " << endl;
			else
				cout << "P[" << i << "] = { " << points[i].x << " ; " << points[i].y << " } " << endl;

			if (i == 99)
				break;
		}

		cout << "=================================== Only top 100 ===============================" << endl << endl;

		if (pause)
			Pause();
	}

	void Console::Print(vector<PointPair> points, bool pause)
	{
		cout << "================================== Print PointPair ========================================" << endl;
		cout << ">> Size: " << points.size() << endl;

		int count = 1;
		for each (PointPair item in points)
		{
			if (count < 10)
				cout << "[0" << count << "] FirstPoint : { " << item.FirstPoint.x << " ; " << item.FirstPoint.y << " } - SecondPoint : { " << item.SecondPoint.x << " ; " << item.SecondPoint.y << " }" << endl;
			else
				cout << "[" << count << "] FirstPoint : { " << item.FirstPoint.x << " ; " << item.FirstPoint.y << " } - SecondPoint : { " << item.SecondPoint.x << " ; " << item.SecondPoint.y << " }" << endl;
			count++;

			if (count == 100)
				break;
		}

		cout << "==================================== Only top 100 ============================================" << endl;

		if (pause)
			Pause();
	}

	void Console::Print(SiftResult siftResult, bool pause)
	{
		cout << "================================== Result SiftResult ===========================================" << endl << endl;

		// Print matches
		Print(siftResult.Matches);

		// temp vector points for keypoints
		vector<Point2f> firstPoints, secondPoints;

		// get vector first points
		for each (KeyPoint pt in siftResult.FirstImageKeyPoints)
			firstPoints.push_back(pt.pt);

		// get vector second points
		for each (KeyPoint pt in siftResult.FirstImageKeyPoints)
			secondPoints.push_back(pt.pt);

		Print(firstPoints);
		Print(secondPoints);
		cout << "==================================== / Result SiftResult ============================================" << endl << endl;

		if (pause)
			Pause();
	}

	void Console::Print(vector<Vec6f> triangles, bool pause)
	{
		cout << "============================= Result vector<Vec6f> =============================" << endl << endl;
		cout << ">> Size: " << triangles.size() << endl;

		for (size_t i = 0; i < triangles.size(); i++) {
			Vec6f triangle = triangles[i];
			Point2f pt1{ triangle[0], triangle[1] };
			Point2f pt2{ triangle[2], triangle[3] };
			Point2f pt3{ triangle[4], triangle[5] };

			cout << "Triangle = { " << PrintString(pt1) << " ; " << PrintString(pt2) << " ; " << PrintString(pt3) << " }" << endl;

			if (i == 99)
				break;
		}

		cout << "============================= Only top 100 =====================================" << endl << endl;

		if (pause)
			Pause();
	}

	void Console::Print(vector<DMatch> matches, bool pause) {
		cout << "============================= Result vector<DMatch> =============================" << endl;
		cout << ">> Size: " << matches.size() << endl;

		for (int i = 0; i < matches.size(); i++) {
			cout << "{ ImgIndex: " << matches[i].imgIdx << " | ";
			cout << "QueryIndex: " << matches[i].queryIdx << " | ";
			cout << "TrainIndex: " << matches[i].trainIdx << " | ";
			cout << "Distance: " << matches[i].distance << " }" << endl;

			if (i == 99)
				break;
		}

		cout << "=============================== Only top 100 ===================================" << endl << endl;

		if (pause)
			Pause();
	}

	void Console::Print(CameraProperties cameraProperties, bool pause)
	{
		cout << "=============================== CameraProperties ===============================" << endl;

		cout << "B: " << cameraProperties.B << endl;
		cout << "Lambda: " << cameraProperties.Lambda << endl;

		cout << "================================================================================" << endl << endl;

		if (pause)
			Pause();
	}

}
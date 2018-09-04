#include "stdafx.h"
#include "Console.h"

namespace Helpers {

	Console::Console()
	{

	}
	
	Console::~Console()
	{
	}	

	void Console::Print(vector<Point3f> listPoints)
	{
		cout << "============================= Result =============================" << endl;
		int count = 1;
		for each (Point3f item in listPoints)
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
	}

	void Console::Print(vector<PointPair> listPoints)
	{
		cout << "================================== Print PointPair ========================================" << endl;
		int count = 1;
		for each (PointPair item in listPoints)
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
	}

	void Console::Print(SiftResult result)
	{

	}

	void Console::Print(vector<Vec6f> triangles) 
	{
		cout << "============================= Result =============================" << endl;
		for (size_t i = 0; i < triangles.size(); i++) {
			Vec6f triangle = triangles[i];
			Point pt1{ cvRound(triangle[0]), cvRound(triangle[1]) };
			Point pt2{ cvRound(triangle[2]), cvRound(triangle[3]) };
			Point pt3{ cvRound(triangle[4]), cvRound(triangle[5]) };

			cout << "Triangle = { " << Print(pt1) << " ; " << Print(pt2) << " ; " << Print(pt3) << " }" << endl;

			if (i == 99)
				break;
		}

		cout << "============================= Only top 100 =====================================" << endl;
	}

	string Console::Print(Point point)
	{
		return "P(" + to_string(point.x) + "," + to_string(point.y) + ")";
	}

	void Console::Print(Point3f point)
	{
		cout << "============================= Result =============================" << endl;
		cout << "Point = { " << point.x << " ; " << point.y << " ; " << point.z << " } " << endl;
		cout << "==================================================================" << endl;
	}
}
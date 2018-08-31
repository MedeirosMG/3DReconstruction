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
		}
		cout << "==================================================================" << endl;
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
		}
		cout << "===========================================================================================" << endl;
	}

	void Console::Print(Point3f point)
	{
		cout << "============================= Result =============================" << endl;
		cout << "Point = { " << point.x << " ; " << point.y << " ; " << point.z << " } " << endl;
		cout << "==================================================================" << endl;
	}
}
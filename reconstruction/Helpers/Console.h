#ifndef HELPERS_CONSOLE
#define HELPERS_CONSOLE
#include <iostream>
#include <fstream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"
#include "../Entities/SiftResult.h"
#include "../Entities/CameraProperties.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;

namespace Helpers {

	static class Console
	{
		private:
			static string PrintString(Point2f point);
			static void Pause();

		public:
			Console();
			~Console();

			static void Print(vector<Point3f> points, bool pause = false);
			static void Print(Point3f point, bool pause = false);
			static void Print(vector<Point2f> points, bool pause = false);
			static void Print(Point2f point, bool pause = false);
			static void Print(vector<vector<Point>> points, bool pause = false);
			static void Print(vector<Point> points, bool pause = false);
			static void Print(vector<PointPair> points, bool pause = false);
			static void Print(SiftResult siftResult, bool pause = false);
			static void Print(vector<Vec6f> triangles, bool pause = false);
			static void Print(vector<DMatch> matches, bool pause = false);
			static void Print(CameraProperties cameraProperties, bool pause = false);
	};

}

#endif
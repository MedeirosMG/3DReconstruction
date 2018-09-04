#ifndef HELPERS_CONSOLE
#define HELPERS_CONSOLE
#include <iostream>
#include <fstream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"
#include "../Entities/SiftResult.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;

namespace Helpers {

	static class Console
	{
		private:
			static string Print(Point point);

		public:
			Console();
			~Console();

			static void Print(vector<Point3f> listPoints);
			static void Print(vector<Point2f> point);
			static void Print(Point3f point);
			static void Print(vector<PointPair> listPoints);
			static void Print(SiftResult result);
			static void Print(vector<Vec6f> triangles);
			static void Print(vector<DMatch> matches);
	};

}

#endif
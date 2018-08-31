#ifndef HELPERS_CONSOLE
#define HELPERS_CONSOLE
#include <iostream>
#include <fstream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;

namespace Helpers {

	static class Console
	{
		public:
			Console();
			~Console();

			static void Print(vector<Point3f> listPoints);
			static void Print(Point3f point);
			static void Print(vector<PointPair> listPoints);
	};

}

#endif
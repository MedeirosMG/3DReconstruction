#ifndef UTILITIES_CUSTOM_POINT
#define UTILITIES_CUSTOM_POINT
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"
#include "../Entities/CustomPoint.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;

namespace Utilities {
	class PointUtilities
	{
		private:
			OpenCV * _openCv;

		public:
			PointUtilities(OpenCV* openCv);
			PointUtilities();
			~PointUtilities();

			Point3f ReturnPoint3f(CustomPoint point);
			vector<Point3f> ReturnPoint3f(vector<CustomPoint> points);
			vector<Point3f> AddValueToPoints(vector<Point3f> points, float maxValue);
			float GetMaxAbsCoord(vector<Point3f> points, string coordinate);
	};
}

#endif
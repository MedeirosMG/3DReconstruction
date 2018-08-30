#ifndef HELPERS_CONVERT
#define HELPERS_CONVERT
#include <iostream>
#include <fstream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"
#include "../Entities/CustomPoint.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;

namespace Helpers {

	class Convert
	{
		private:
			OpenCV * _openCv;

		public:
			Convert(OpenCV* openCv);
			Convert();
			~Convert();

			static Point3f CustomPointTo3f(CustomPoint point);
			static vector<Point3f> CustomPointTo3f(vector<CustomPoint> points);

			static Point2f CustomPointTo2f(CustomPoint point);
			static vector<Point2f> CustomPointTo2f(vector<CustomPoint> points);
	};

}

#endif
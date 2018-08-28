#ifndef UTILITIES_CUSTOM_POINT
#define UTILITIES_CUSTOM_POINT
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"
#include "../Entities/CustomPoint.h"

using namespace std;
using namespace Algorithms;

namespace Utilities {
	class CustomPoint
	{
		private:
			OpenCV * _openCv;

		public:
			CustomPoint(OpenCV* openCv);
			CustomPoint();
			~CustomPoint();
	};
}

#endif
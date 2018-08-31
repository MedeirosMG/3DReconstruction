#ifndef HELPERS_EXPORT
#define HELPERS_EXPORT
#include <iostream>
#include <fstream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;

namespace Helpers {

	static class Export
	{
		public:
			Export();
			~Export();

			bool Json(vector<Point3f> listPoints, string pathDirectory);
			bool Obj(vector<Point3f> listPoints, string pathDirectory);
	};

}

#endif
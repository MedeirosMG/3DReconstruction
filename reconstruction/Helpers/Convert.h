#ifndef HELPERS_CONVERT
#define HELPERS_CONVERT
#include <iostream>
#include <fstream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"

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

			static Point3f Point3fTo3f(Point3f point);
			static vector<Point3f> Point3fTo3f(vector<Point3f> points);

			static Point2f Point3fTo2f(Point3f point);
			static vector<Point2f> Point3fTo2f(vector<Point3f> points);

			static vector<PointPair> DMatchToPointPair(vector<DMatch> matches, vector<KeyPoint> firstImageKeyPoints, vector<KeyPoint> secondImageKeyPoints);
	};

}

#endif
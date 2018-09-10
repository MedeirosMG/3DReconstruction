#ifndef HELPERS_POINT_UTILITIES
#define HELPERS_POINT_UTILITIES
#include <iostream>
#include <fstream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;

namespace Helpers {

	class PointUtilities
	{
		private:
			OpenCV * _openCv;

		public:
			PointUtilities(OpenCV* openCv);
			PointUtilities();
			~PointUtilities();

			vector<Point3f> PointsTranslocate(vector<Point3f> points, float maxValue);
			vector<Vec6f> PointsTranslocate(vector<Vec6f> points, float maxValue);
			vector<Point3f> PointsZoom(vector<Point3f> points, int zoom);
			float GetMaxAbsCoord(vector<Point3f> points, string coordinate);
			float GetMaxAbsCoord(vector<Vec6f> points);
			vector<Point3f> GetMockPoints(string fileRead = ".\\Others Files\\MockPoints.obj");
			Point2f GetMiddlePoint(Point2f pt1, Point2f pt2);
			vector<Point3f> MergePoints(vector<Point3f> pts1, vector<Point3f> pts2);
	};

}

#endif
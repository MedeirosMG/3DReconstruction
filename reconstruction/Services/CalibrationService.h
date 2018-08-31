#ifndef SERVICES_CALIBRATION
#define SERVICES_CALIBRATION
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;
using namespace Algorithms;
using namespace Entities;

namespace Services {

	class CalibrationService
	{
		private:
			OpenCV * _openCv;
			float _b;
			float _lambda;
			int _k = 1;

		protected:
			float WorldPointX(float firstPointX, float Z);
			float WorldPointY(float firstPointY, float Z);
			float WorldPointZ(Point3f firstPoint, Point3f secondPoint);

		public:
			CalibrationService(float b, float lambda, OpenCV* openCv, int k = 1);
			CalibrationService(OpenCV* openCv);
			~CalibrationService();

			vector<Point3f> CalculateStereoCameraCalibration(vector<PointPair> listMatchPoints);
			Point3f* CalculateRealPoint(Point3f firstPoint, Point3f secondPoint);
			void OrderPointsByAsc(vector<Point3f>& listPoints);
	};

}

#endif
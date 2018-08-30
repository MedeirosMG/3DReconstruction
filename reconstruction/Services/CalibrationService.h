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

	// Implementar funções do Calibration
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
			Point3f BestNeighbour(Point3f checkPoint, vector<Point3f> listNeighbourPoint);
			vector<Point3f> GetNeighbourPoints(vector<Point3f>listPointsFrame, int positionPointFrame);
			vector<Point3f> CalculateListRealPoints(vector<PointPair> listPoints);
			float CalculateEuclideanDistance(Point3f firstPoint, Point3f secondPoint);

		public:
			CalibrationService(float b, float lambda, OpenCV* openCv, int k = 1);
			CalibrationService(OpenCV* openCv);
			~CalibrationService();

			vector<Point3f> CalculateStereoCameraCalibration(vector<PointPair> listMatchPoints);
			vector<Point3f> CalculateStereoCameraCalibrationUsingNeighbours(vector<Point3f> listPointsFrame1, vector<Point3f> listPointsFrame2);
			Point3f* CalculateRealPoint(Point3f firstPoint, Point3f secondPoint);
			void PrintResult(vector<Point3f> listPoints);
			void PrintResult(Point3f point);
			void PrintResult(vector<PointPair> listPoints);
			bool ExportToJson(vector<Point3f> listPoints, string pathDirectory);
			bool ExportToObj(vector<Point3f> listPoints, string pathDirectory);
			void OrderPointsByAsc(vector<Point3f>& listPoints);
			void PivelToCoordinate(vector<PointPair>& listPoints);
			void ChangeScale(vector<Point3f>& listPoints);
			void ChangeScale(vector<PointPair>& listPoints);
			vector<Point3f> FilterByShape(vector<Point3f> listPoints, vector<Point3f> listShapePoints);
	};

}

#endif
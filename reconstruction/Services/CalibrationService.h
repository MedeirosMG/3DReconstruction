#ifndef SERVICES_CALIBRATION
#define SERVICES_CALIBRATION
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"
#include "../Entities/CustomPoint.h"
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
			float WorldPointZ(CustomPoint firstPoint, CustomPoint secondPoint);
			CustomPoint BestNeighbour(CustomPoint checkPoint, vector<CustomPoint> listNeighbourPoint);
			vector<CustomPoint> GetNeighbourPoints(vector<CustomPoint>listPointsFrame, int positionPointFrame);
			vector<CustomPoint> CalculateListRealPoints(vector<PointPair> listPoints);
			float CalculateEuclideanDistance(CustomPoint firstPoint, CustomPoint secondPoint);

		public:
			CalibrationService(float b, float lambda, OpenCV* openCv, int k = 1);
			CalibrationService(OpenCV* openCv);
			~CalibrationService();

			vector<CustomPoint> CalculateStereoCameraCalibration(vector<PointPair> listMatchPoints);
			vector<CustomPoint> CalculateStereoCameraCalibrationUsingNeighbours(vector<CustomPoint> listPointsFrame1, vector<CustomPoint> listPointsFrame2);
			CustomPoint* CalculateRealPoint(CustomPoint firstPoint, CustomPoint secondPoint);
			void PrintResult(vector<CustomPoint> listPoints);
			void PrintResult(CustomPoint point);
			void PrintResult(vector<PointPair> listPoints);
			bool ExportToJson(vector<CustomPoint> listPoints, string pathDirectory);
			bool ExportToObj(vector<CustomPoint> listPoints, string pathDirectory);
			void OrderPointsByAsc(vector<CustomPoint>& listPoints);
			void PivelToCoordinate(vector<PointPair>& listPoints);
			void ChangeScale(vector<CustomPoint>& listPoints);
			void ChangeScale(vector<PointPair>& listPoints);
			vector<CustomPoint> FilterByShape(vector<CustomPoint> listPoints, vector<CustomPoint> listShapePoints);
	};

}

#endif
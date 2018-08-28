#ifndef SERVICES_DELAUNAY
#define SERVICES_DELAUNAY
#include <iostream>
#include <fstream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"
#include "../Entities/CustomPoint.h"
#include "../Helpers/PointsUtilities.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;
using namespace Utilities;

namespace Services {

	// Implementar funções do Delaunay utilizando os Algorithms
	class DelaunayService
	{
		private:
			OpenCV* _openCv;

		public:
			DelaunayService(OpenCV* openCv);
			DelaunayService();
			~DelaunayService();
			vector<Vec6f> Execute(vector<CustomPoint> points, int zoom);
			vector<CustomPoint> MockPoints();
			void TestExecute(vector<CustomPoint> points = vector<CustomPoint>());
	};

}

#endif
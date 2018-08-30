#ifndef SERVICES_DELAUNAY
#define SERVICES_DELAUNAY
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"
#include "../Entities/CustomPoint.h"
#include "../Helpers/PointsUtilities.h"
#include "../Helpers/Convert.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;
using namespace Helpers;

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
			vector<Vec6f> Execute(vector<CustomPoint> points);
			void TestExecute(vector<CustomPoint> points = vector<CustomPoint>());
			vector<Vec6f> RemoveRectangle(vector<Vec6f> triangles);
			bool CheckRectangle(int coord, Vec6f triangle);
	};

}

#endif
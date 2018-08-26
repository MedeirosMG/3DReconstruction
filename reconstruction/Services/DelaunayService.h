#ifndef SERVICES_DELAUNAY
#define SERVICES_DELAUNAY
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"
#include "../Entities/CustomPoint.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;

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
			vector<CustomPoint> MockPoints();
			void TestExecute();
	};

}

#endif
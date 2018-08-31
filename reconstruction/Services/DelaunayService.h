#ifndef SERVICES_DELAUNAY
#define SERVICES_DELAUNAY
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"
#include "../Helpers/PointsUtilities.h"
#include "../Helpers/Convert.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;
using namespace Helpers;

namespace Services {

	// Implementar fun��es do Delaunay utilizando os Algorithms
	class DelaunayService
	{
		private:
			OpenCV* _openCv;

		public:
			DelaunayService(OpenCV* openCv);
			DelaunayService();
			~DelaunayService();
			vector<Vec6f> Execute(vector<Point3f> points);
			void TestExecute(vector<Point3f> points = vector<Point3f>());
			vector<Vec6f> RemoveRectangle(vector<Vec6f> triangles);
			bool CheckRectangle(int coord, Vec6f triangle);
	};

}

#endif
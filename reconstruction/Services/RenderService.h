#ifndef ALGORITHMS_RENDER
#define ALGORITHMS_RENDER
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/CustomPoint.h"
#include "../Helpers/PointsUtilities.h"
#include "../Services/DelaunayService.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;
using namespace Helpers;

namespace Services {

	// Implementar funções do Calibration
	class RenderService
	{
		private:
			OpenCV * _openCv;
			static vector<Vec6f> _triangles;
			static vector<Point3f> _points3D;
			void Init(int width, int height, vector<Vec6f> triangles, vector<Point3f> points3D);

		public:
			RenderService(OpenCV* openCv);
			RenderService();
			~RenderService();
			void TestExecute(int *argc, char **argv, vector<CustomPoint> points = vector<CustomPoint>());
			void Execute(int *argc, char **argv, vector<Vec6f> triangles, vector<CustomPoint> points3D);
			vector<Vec6f> GetTriangles();
			vector<Point3f> GetPoints();
	};

}

#endif

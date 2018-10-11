#ifndef ALGORITHMS_RENDER
#define ALGORITHMS_RENDER
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Helpers/PointsUtilities.h"
#include "../Entities/RenderProperties.h"
#include "../Helpers/Convert.h"
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
			void Init(int width, int height, vector<Vec<Point3f, 3>> triangles, vector<Point3f> points3D);

		public:
			RenderService(OpenCV* openCv);
			RenderService();
			~RenderService();
			void TestExecute(int *argc, char **argv, vector<Point3f> points = vector<Point3f>());
			void Execute(int *argc, char **argv, vector<Vec<Point3f, 3>> triangles, vector<Point3f> points3D);

			static RenderProperties *_renderProperties;
	};

}

#endif

#ifndef ALGORITHMS_RENDER
#define ALGORITHMS_RENDER
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/CustomPoint.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;

namespace Services {

	// Implementar funções do Calibration
	class RenderService
	{
		private:
			OpenCV * _openCv;
			void Init();

		public:
			RenderService(OpenCV* openCv);
			RenderService();
			~RenderService();
			void Execute(int *argc, char **argv, vector<Vec6f> triangles, vector<CustomPoint> points3D);
	};

}

#endif

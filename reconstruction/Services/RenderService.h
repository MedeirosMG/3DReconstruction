#ifndef ALGORITHMS_RENDER
#define ALGORITHMS_RENDER
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"

using namespace std;
using namespace Algorithms;

namespace Services {

	// Implementar funções do Calibration
	class RenderService
	{
		private:
			OpenCV * _openCv;

		public:
			RenderService(OpenCV* openCv);
			RenderService();
			~RenderService();
			void Execute(int *argc, char **argv);
	};

}

#endif

#ifndef SERVICES_RANSAC
#define SERVICES_RANSAC
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"

using namespace std;
using namespace Algorithms;

namespace Services {

	// Implementar funções do Ransac utilizando os Algorithms
	class RansacService
	{
		private:
			OpenCV * _openCv;

		public:
			RansacService();
			RansacService(OpenCV* openCv);
			~RansacService();
	};

}

#endif
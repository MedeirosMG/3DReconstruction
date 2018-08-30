#ifndef SERVICES_RANSAC
#define SERVICES_RANSAC
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;

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
			vector<PointPair> Execute(vector<PointPair> points, double ransacThresh = 3.0);
	};

}

#endif
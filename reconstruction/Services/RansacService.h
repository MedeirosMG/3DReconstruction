#ifndef SERVICES_RANSAC
#define SERVICES_RANSAC
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"
#include "../Entities/SiftResult.h"
#include "../Helpers/Convert.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;
using namespace Helpers;

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
			Mat FindRansacMask(SiftResult sift_result, double ransacThresh);
			vector<PointPair> Execute(SiftResult sift_result, double ransacThresh = 3.0);
	};

}

#endif
#ifndef SERVICES_SIFT
#define SERVICES_SIFT

#include <iostream>
#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"
#include "../Entities/ResultSift.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;

namespace Services {

	class SiftService
	{
		private:
			OpenCV * _openCv;

		public:
			SiftService();
			SiftService(OpenCV* openCv);
			~SiftService();
			ResultSift Execute(Mat img1, Mat img2, int threshold);
	};
	
}

#endif
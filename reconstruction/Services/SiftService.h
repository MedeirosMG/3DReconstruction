#ifndef SERVICES_SIFT
#define SERVICES_SIFT

#include <iostream>
#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"

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
			vector<PointPair> Execute(Mat img1, Mat img2, int threshold);
	};
	
}

#endif
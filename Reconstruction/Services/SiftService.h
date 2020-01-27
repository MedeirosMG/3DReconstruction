#ifndef SERVICES_SIFT
#define SERVICES_SIFT

#include <iostream>
#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"
#include "../Entities/SiftResult.h"
#include "../Services/RansacService.h"

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
			SiftResult Execute(Mat img1, Mat img2, int features, int layers, double contrast, double edge, double sigma);
			SiftResult Execute(Mat img1, Mat img2, Mat mask1, Mat mask2, int features, int layers, double contrast, double edge, double sigma);
	};
	
}

#endif
#ifndef SERVICES_FIND_REGIONS
#define SERVICES_FIND_REGIONS
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Helpers/PFM.h"
#include "../Helpers/PointsUtilities.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;
using namespace Algorithms;
using namespace Helpers;

namespace Services {

	// Implementar fun��es do FindRegions utilizando os Algorithms
	class ReconstructionCompareService
	{
		private:
			OpenCV * _openCv;

		public:
			ReconstructionCompareService();
			ReconstructionCompareService(OpenCV* openCv);
			~ReconstructionCompareService();
			void Execute(vector<Point3f> reconstructionPoints, string pathMap, string pathExport);
	};

}

#endif
#ifndef SERVICES_RECONSTRUCTION_COMPARE
#define SERVICES_RECONSTRUCTION_COMPARE
#include <iostream>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Helpers/PFM.h"
#include "../Helpers/PointsUtilities.h"
#include "../Helpers/Export.h"
#include "../Helpers/ReconstructionDefine.h"
#include "../Helpers/StringHelper.h"
#include "../Entities/ReconstructionComparison.h"

using namespace cv;
using namespace std;
using namespace Algorithms;
using namespace Helpers;
using namespace Entities;

namespace Services {

	// Implementar funções do FindRegions utilizando os Algorithms
	class ReconstructionCompareService
	{
		private:
			OpenCV * _openCv;

		public:
			ReconstructionCompareService();
			ReconstructionCompareService(OpenCV* openCv);
			~ReconstructionCompareService();
			void Execute(vector<Point3f> reconstructionPoints, CameraProperties calib, string pathMap, string pathExport);
			void Execute(vector<Point3f> reconstructionPoints, CameraProperties calib, string pathMap, string pathExport, map<string, double> batchResult);
	};

}

#endif
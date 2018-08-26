#ifndef SERVICES_FIND_REGIONS
#define SERVICES_FIND_REGIONS
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;
using namespace Algorithms;

namespace Services {

	// Implementar funções do FindRegions utilizando os Algorithms
	class FindRegionsService
	{
		private:
			OpenCV * _openCv;

		public:
			FindRegionsService();
			FindRegionsService(OpenCV* openCv);
			~FindRegionsService();
			Mat Execute(Mat regioes, string caminhoImg);
			Mat Execute(Mat regioes, Mat imgOriginal);
	};

}

#endif
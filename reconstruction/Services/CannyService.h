#ifndef SERVICES_CANNY
#define SERVICES_CANNY
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"

using namespace std;
using namespace Algorithms;

namespace Services {

	// Implementar funções do Canny utilizando os Algorithms
	class CannyService
	{
		private:
			OpenCV* _openCv;

		public:
			CannyService();
			CannyService(OpenCV* openCv);
			~CannyService();
			Mat Execute(Mat inputImage, double lowThresh, double highThresh, int kernelSize);
	};

}

#endif
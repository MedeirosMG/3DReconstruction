#ifndef SERVICES_COMPONENTS_CONNECTED
#define SERVICES_COMPONENTS_CONNECTED
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"

using namespace std;
using namespace Algorithms;

namespace Services {

	// Implementar funções do ComponentsConnected utilizando os Algorithms
	class ConnectedComponentsService
	{
		private:
			OpenCV* _openCv;

		public:
			ConnectedComponentsService();
			ConnectedComponentsService(OpenCV* openCV);
			~ConnectedComponentsService();
			Mat Execute(Mat img, int threshVal);
	};

}

#endif
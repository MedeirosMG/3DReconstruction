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
		OpenCV * _openCv;
		float _threshold;

	public:
		ConnectedComponentsService();
		ConnectedComponentsService(OpenCV* openCV);
		ConnectedComponentsService(OpenCV* openCV, float threshold);
		~ConnectedComponentsService();
		Mat Execute(Mat img);
	};

}

#endif
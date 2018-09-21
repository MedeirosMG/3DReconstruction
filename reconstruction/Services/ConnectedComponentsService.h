#ifndef SERVICES_COMPONENTS_CONNECTED
#define SERVICES_COMPONENTS_CONNECTED
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Helpers/ReconstructionDefine.h"
#include "../Helpers/PointsUtilities.h"
#include "../Helpers/Console.h"

using namespace std;
using namespace Algorithms;
using namespace Helpers;

namespace Services {

	// Implementar funções do ComponentsConnected utilizando os Algorithms
	class ConnectedComponentsService
	{
	private:
		OpenCV * _openCv;
		float _threshold = 0.0;
		vector<vector<Point>> Filter(vector<vector<Point>> contours);
		Size _screenSize = Size(REC_SCREEN_DEFAULT_WIDTH, REC_SCREEN_DEFAULT_HEIGHT);

	public:
		ConnectedComponentsService();
		ConnectedComponentsService(OpenCV* openCV);
		ConnectedComponentsService(OpenCV* openCV, Size imgSize);
		ConnectedComponentsService(OpenCV* openCV, Size imgSize, float threshold);
		~ConnectedComponentsService();
		Mat Execute(Mat img);
	};

}

#endif
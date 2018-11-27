#ifndef HELPERS_CAMERA_CAPTURE
#define HELPERS_CAMERA_CAPTURE
#include <iostream>
#include <fstream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Helpers/StringHelper.h"

using namespace std;
using namespace Algorithms;

namespace Helpers {

	class CameraCapture
	{
		public:
			CameraCapture();
			~CameraCapture();

			static bool Visualize(bool showGrid);
			static bool Capture(string pathExport, bool showGrid = false, bool exportGrid = false);
	};

}

#endif
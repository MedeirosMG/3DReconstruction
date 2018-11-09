#ifndef SERVICES_INPUT_IMAGE
#define SERVICES_INPUT_IMAGE

#include <iostream>
#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;

namespace Services {

	class InputImageService
	{
		private:
			OpenCV * _openCv;

		public:
			InputImageService();
			InputImageService(OpenCV* openCv);
			~InputImageService();
			Mat Execute(string path);
	};
	
}

#endif
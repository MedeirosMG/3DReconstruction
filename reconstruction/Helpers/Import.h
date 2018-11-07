#ifndef HELPERS_IMPORT
#define HELPERS_IMPORT
#include <iostream>
#include <fstream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Helpers/Time.h"
#include "../Helpers/StringHelper.h"
#include "../Entities/CameraProperties.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;

namespace Helpers {

	class Import
	{
		public:
			Import();
			~Import();

			static vector<TimeExecution> Csv(string pathDirectory);
			static CameraProperties CameraParameters(string pathDirectory);
			static vector<CameraProperties> CameraParameters(vector<string> pathDirectory);
	};
}

#endif
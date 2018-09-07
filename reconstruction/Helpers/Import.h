#ifndef HELPERS_IMPORT
#define HELPERS_IMPORT
#include <iostream>
#include <fstream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Helpers/Time.h"
#include "../Helpers/StringHelper.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;

namespace Helpers {
	class Time;

	class Import
	{
		public:
			Import();
			~Import();

			static vector<TimeExecution> Csv(string pathDirectory);
	};
}

#endif
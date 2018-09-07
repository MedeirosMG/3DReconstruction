#ifndef HELPERS_STRING
#define HELPERS_STRING
#include <iostream>
#include <fstream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"
#include "../Helpers/Time.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;

namespace Helpers {

	static class StringHelper
	{
		public:
			StringHelper();
			~StringHelper();
			
			static vector<string> Split(const string& str, const char& splitter);
	};

}

#endif
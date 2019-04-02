#ifndef HELPERS_IMPORT
#define HELPERS_IMPORT
#include <iostream>
#include <fstream>
#include <experimental/filesystem>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Helpers/Time.h"
#include "../Helpers/StringHelper.h"
#include "../Helpers/Mathematic.h"
#include "../Entities/CameraProperties.h"
#include "../Entities/AverageDeviationStd.h"

namespace fs = std::experimental::filesystem;
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
			static void CalculateAverage(string pathDirectory, map<string, double>& result);
			static void CalculateAverage(string pathDirectory, map<string, AverageDeviationStd*>& result);
			static CameraProperties CameraParameters(string pathDirectory);
			static vector<CameraProperties> CameraParameters(vector<string> pathDirectory);
			static vector<vector<float>> HeartDepthMapFloat(string pathDirectory, int columnSize);
			static vector<vector<Point3f>> HeartDepthMap(string pathDirectory, int columnSize);
			static CameraProperties HeartCameraParameters(string path_calib_left, string path_calib_right);
	};
}

#endif
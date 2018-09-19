#ifndef SERVICES_FIREFLY
#define SERVICES_FIREFLY
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Algorithms/Firefly.h"
#include "../Helpers/MultiThreshold.h"

using namespace std;
using namespace Algorithms;
using namespace Helpers;

namespace Services {

	class FireflyService
	{
		private:
			OpenCV* _openCv;
			Firefly* _firefly;
			MultiThreshold* _multiThreshold;

		public:
			FireflyService();
			FireflyService(OpenCV* openCv);
			~FireflyService();
			Mat Execute(Mat img, int n_thresholds, int n_fireflies, int n_generations);
			void TestExecute(Mat img, int n_thresholds, int n_fireflies, int n_generations);
			void TestExecute(string imgPath, int n_thresholds, int n_fireflies, int n_generations);
	};

}

#endif
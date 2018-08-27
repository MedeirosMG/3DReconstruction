#ifndef SERVICES_FIREFLY
#define SERVICES_FIREFLY
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"


using namespace std;
using namespace Algorithms;

namespace Services {

	// Implementar funções do Firefly utilizando os Algorithms
	class FireflyService
	{
		private:
			OpenCV * _openCv;

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
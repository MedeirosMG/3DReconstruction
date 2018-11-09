#ifndef AUTOMATED_TEST_TEST_SERVICE
#define AUTOMATED_TEST_TEST_SERVICE
#include <iostream>
#include "..\Services\ControllerService.h"
#include "..\Helpers\Time.h"
#include "..\Helpers\Console.h"

using namespace std;
using namespace Helpers;
using namespace Services;

namespace AutomatedTests {

	class TestService
	{
		private:
			Time* _time;

		public:
			TestService();
			~TestService();
			void ReconstructionFF_FP();
			void Reconstruction_FF();
			void Reconstruction_FP();
			void ReconstructionWithTimeExecution();
			void Reconstruction_Default();
			void Canny();
			void Firefly();
			void Render(int argc, char **argv);
			void Delaunay();
			void Ransac();
			void ConnectedComponents();
			void ReconstructionComparison();
	};

}

#endif
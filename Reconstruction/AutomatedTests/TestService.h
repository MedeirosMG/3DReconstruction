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
			void ReconstructionFF_FP(string path_calib, string path_img1, string path_img2, string path_disparity, string path_export);
			void Reconstruction_FF(string path_calib, string path_img1, string path_img2, string path_disparity, string path_export);
			void Reconstruction_FP(string path_calib, string path_img1, string path_img2, string path_disparity, string path_export);
			void Reconstruction_Default(string path_calib, string path_img1, string path_img2, string path_disparity, string path_export);
			void ReconstructionWithTimeExecution(string path_calib, string path_img1, string path_img2, string path_disparity, string path_export);
	};

}

#endif
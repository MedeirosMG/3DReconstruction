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
			void ReconstructionFF_FP(string path_img1, string path_img2, string path_calib, string path_disparity, string path_export_CSV = "", string path_export_OBJ = "", map<string, double>* _resultBatch = NULL, int calibB = 0, int calibLambda = 0);
			void Reconstruction_FF(string path_img1, string path_img2, string path_calib, string path_disparity, string path_export_CSV = "", string path_export_OBJ = "", map<string, double>* _resultBatch = NULL, int calibB = 0, int calibLambda = 0);
			void Reconstruction_FP(string path_img1, string path_img2, string path_calib, string path_disparity, string path_export_CSV = "", string path_export_OBJ = "", map<string, double>* _resultBatch = NULL, int calibB = 0, int calibLambda = 0);
			void Reconstruction_Default(string path_img1, string path_img2, string path_calib, string path_disparity, string path_export_CSV = "", string path_export_OBJ = "", map<string, double>* _resultBatch = NULL, int calibB = 0, int calibLambda = 0);
			void ReconstructionWithTimeExecution(string path_calib, string path_img1, string path_img2, string path_disparity, string path_export);
	};

}

#endif
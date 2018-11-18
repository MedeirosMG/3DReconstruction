#include "stdafx.h"
#include "BatchReconstruction.h"

namespace AutomatedTests {
	/*  string path_calib = ".\\Others Files\\Cable-perfect\\calib.txt";
		string path_img1 = ".\\Others Files\\Cable-perfect\\im0.png";
		string path_img2 = ".\\Others Files\\Cable-perfect\\im1.png";
		string path_disparity = ".\\Others Files\\Cable-perfect\\disp0.pfm";
		string path_export = ".\\Others Files\\results.csv";

		string path_unstructured1 = ".\\Others Files\\unstructured01.png";
		string path_unstructured2 = ".\\Others Files\\unstructured02.png";*/

	BatchReconstruction::BatchReconstruction()
	{
		_time = new Time();
	}

	BatchReconstruction::~BatchReconstruction()
	{
	}

	void BatchReconstruction::Add(string pathFirstStructuredImage, string pathSecondStructuredImage, string pathFirstUnstructuredImage,
		string pathSecondUnstructuredImage, string pathCalib, string pathDisparity, string pathExportComparison)
	{
		ReconstructionTest obj;
		obj.PathCalib = pathCalib;
		obj.PathDisparity = pathDisparity;
		obj.PathExportComparison = pathExportComparison;
		obj.PathFirstStructuredImage = pathFirstStructuredImage;
		obj.PathSecondStructuredImage = pathSecondStructuredImage;
		obj.PathFirstUnstructuredImage = pathFirstUnstructuredImage;
		obj.PathSecondUnstructuredImage = pathFirstUnstructuredImage;

		ListReconstructions.push_back(obj);
	}


#pragma region [ Load Properties Methods ]

	void BatchReconstruction::LoadPropertiesExample()
	{
		for (int i = 0; i < 10; i++)
		{
			Add(
				".\\Others Files\\Cable-perfect\\im0_" + to_string(i) + ".png",
				".\\Others Files\\Cable-perfect\\im1_" + to_string(i) + ".png",
				".\\Others Files\\unstructured01_" + to_string(i) + ".png",
				".\\Others Files\\unstructured02_" + to_string(i) + ".png",
				".\\Others Files\\Cable-perfect\\calib_" + to_string(i) + ".txt",
				".\\Others Files\\Cable-perfect\\disp0_" + to_string(i) + ".pfm",
				".\\Others Files\\results_" + to_string(i) + ".csv"
			);
		}
	}

#pragma endregion


#pragma region [ Test Methods ]

	void BatchReconstruction::Example()
	{
		map<string, double> _resultBatch;

		LoadPropertiesExample();

		// Example!!!!
		for each (ReconstructionTest reconstruction in ListReconstructions)
		{
			cout << "======= Starting Example Automated Test ======= " << endl;

			ControllerService* controller = new ControllerService(reconstruction.PathFirstStructuredImage, reconstruction.PathSecondStructuredImage, _resultBatch);
			controller->SetFireflyProperties(3, 100, 100);
			controller->SetCannyProperties(100, 250, 3);
			controller->SetGeneralProperties();
			controller->SetSiftProperties(0);
			controller->SetCalibrationProperties(reconstruction.PathCalib, reconstruction.PathDisparity, reconstruction.PathExportComparison);
			controller->SetSiftFilterProperties(20, 500);
			controller->SetVisualizerProperties(false);
			controller->LoadServices();

			controller->FireflyApply();
			controller->CannyApply();
			controller->ConnectedComponentsApply();
			controller->FindRegionsApply();
			controller->SiftOnMaskApply();
			controller->SiftOnMaskFilterApply();
			controller->ConvertSiftApply();
			controller->CalibrationApply();
			controller->DelaunayApply();
			controller->RenderApply();

			cout << "======== End Example Automated Test ======== " << endl;
		}

		Export::Csv(_resultBatch, ".\\Others Files\\result_final.csv");
	}

#pragma endregion	

}


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

	void BatchReconstruction::Test()
	{
		int i = 0;
		map<string, double> resultBatchFFFP;
		map<string, double> resultBatchFF;
		map<string, double> resultBatchFP;
		map<string, double> resultBatchDefault;

		AutomatedTests::TestService* testService = new AutomatedTests::TestService();

		vector<string> paths_base;
		// Get all paths in structure images
		for (auto & p : fs::directory_iterator(".\\Structured_Images"))
			paths_base.push_back(p.path().string());

		// Run test in all paths
		for each (string path in paths_base)
		{
			int total = paths_base.size();

			cout << "--------------------------------------------------------------------" << endl;
			cout << "Executing: " + path.substr(path.find("s\\") + 2, path.size()) << endl;
			cout << "Progress: " + to_string(i) + " | " + to_string(total) << endl;
			cout << "--------------------------------------------------------------------" << endl << endl << endl << endl;

			string export_path_FFFP = ".\\Reports\\Export_Result\\FF_FP\\" + path.substr(path.find("s\\") + 2, path.size());
			string export_path_FF = ".\\Reports\\Export_Result\\FF\\" + path.substr(path.find("s\\") + 2, path.size());
			string export_path_FP = ".\\Reports\\Export_Result\\FP\\" + path.substr(path.find("s\\") + 2, path.size());
			string export_path_Default = ".\\Reports\\Export_Result\\DEFAULT\\" + path.substr(path.find("s\\") + 2, path.size());

			testService->ReconstructionFF_FP(
				path + "\\im1.png",
				path + "\\im0.png", 
				path + "\\calib.txt",
				path + "\\disp0.pfm",
				export_path_FFFP + "_FF_FP.csv",
				"",
				&resultBatchFFFP);

			testService->Reconstruction_FF(
				path + "\\im1.png",
				path + "\\im0.png",
				path + "\\calib.txt",
				path + "\\disp0.pfm",
				export_path_FF + "_FF.csv",
				"",
				&resultBatchFF);

			testService->Reconstruction_FP(
				path + "\\im1.png",
				path + "\\im0.png",
				path + "\\calib.txt",
				path + "\\disp0.pfm",
				export_path_FP + "_FP.csv",
				"",
				&resultBatchFP);

			testService->Reconstruction_Default(
				path + "\\im1.png",
				path + "\\im0.png",
				path + "\\calib.txt",
				path + "\\disp0.pfm",
				export_path_Default + "_DEF.csv",
				"",
				&resultBatchDefault);

			i++;

			system("cls");
		}

		Export::Csv(resultBatchFFFP, ".\\Reports\\Structured\\resultBatchFFFP.csv");
		Export::Csv(resultBatchFF, ".\\Reports\\Structured\\resultBatchFF.csv");
		Export::Csv(resultBatchFP, ".\\Reports\\Structured\\resultBatchFP.csv");
		Export::Csv(resultBatchDefault, ".\\Reports\\Structured\\resultBatchDefault.csv");
	}


	void BatchReconstruction::TestHeartDepthMap(string path_calib_left, string path_calib_right, string path_img1, string path_img2, string basePathDepthMap, string basePathDisparityMap) {
		map<string, double> resultBatchFFFP;
		map<string, double> resultBatchFF;
		map<string, double> resultBatchFP;
		map<string, double> resultBatchDefault;
		vector<string> paths_base_left;
		vector<string> paths_base_right;
		int count = 0;
		int depthMapCount = -1;
		string pathDepthMap = "";
		string pathDisparityMap;

		OpenCV openCv;
		PointUtilities *pointUtilities = new PointUtilities();
		AutomatedTests::TestService* testService = new AutomatedTests::TestService();
		CameraProperties camera = Import::HeartCameraParameters(path_calib_left, path_calib_right);

		// Get all paths in structure images
		for (auto & p : fs::directory_iterator(path_img1))
			paths_base_left.push_back(p.path().string());

		// Get all paths in structure images
		for (auto & p : fs::directory_iterator(path_img2))
			paths_base_right.push_back(p.path().string());

		std::sort(paths_base_left.begin(), paths_base_left.end());
		std::sort(paths_base_right.begin(), paths_base_right.end());

		for (int frameNo = 0; frameNo < paths_base_left.size(); frameNo++)
		{
			pathDisparityMap = "";
			Mat imgLeft = openCv.ReadImage(paths_base_left[frameNo]);
			Mat imgRight = openCv.ReadImage(paths_base_right[frameNo]);
			// Original Equation: round(mod((FrameNo/25 + 0.466667)*30,20))
			//depthMapCount = (int)std::round((frameNo / 25.0 + 0.466667) * 30.0) % 20;

			StringHelper::Append(pathDepthMap, basePathDepthMap);
			StringHelper::Append(pathDepthMap, to_string(frameNo));
			StringHelper::Append(pathDepthMap, ".txt");

			StringHelper::Append(pathDisparityMap, basePathDisparityMap);
			StringHelper::Append(pathDisparityMap, to_string(frameNo));
			StringHelper::Append(pathDisparityMap, ".txt");

			cout << pathDisparityMap << endl;
			vector<float> matrizDisparityZ = Import::HeartDisparityMap(pathDisparityMap);
			//vector<vector<float>> matrizDepthZ = Import::HeartDepthMapFloat(pathDepthMap, 360);
			//vector<vector<Point3f>> matrizDepthMat = Import::HeartDepthMap(pathDepthMap, 360);

			/*float maxDepthMap = pointUtilities->GetMaxAbsCoord(matrizDepthMat, "z", true);
			float minDepthMap = pointUtilities->GetMinAbsCoord(matrizDepthMat, "z", true);
			vector<uchar> matrizDepthMatNormalizedZ;

			for each (vector<float> row in matrizDepthZ)
			{
				for each (float z in row)
				{
					matrizDepthMatNormalizedZ.push_back(Mathematic::Normalize(z, minDepthMap, maxDepthMap));
				}
			}

			Mat depthMap(288, 360, 0, matrizDepthMatNormalizedZ.data());
			flip(depthMap, depthMap, 1);*/
			//openCv.ShowImage(depthMap, "Depth Map");

			float maxDisparityMap = pointUtilities->GetMaxAbsCoord(matrizDisparityZ, true);
			float minDisparityMap = pointUtilities->GetMinAbsCoord(matrizDisparityZ, true);
			vector<float> matrizDisparityMatNormalizedZ;

			for each (float z in matrizDisparityZ) {
				float normalizedZ = Mathematic::Normalize(z, minDisparityMap, maxDisparityMap);
				matrizDisparityMatNormalizedZ.push_back(normalizedZ < 0 ? 0 : normalizedZ);
			}

			Mat disparityMap(288, 360, 5, matrizDisparityMatNormalizedZ.data());
			flip(disparityMap, disparityMap, 1);
			//openCv.ShowImage(disparityMap, "Disparity Map");

			cout << "--------------------------------------------------------------------" << endl;
			cout << "Executing: " + to_string(frameNo) << endl;
			cout << "Progress: " + to_string(frameNo) + " | " + to_string(paths_base_left.size()) << endl;
			cout << "--------------------------------------------------------------------" << endl << endl << endl << endl;

			testService->ReconstructionFF_FP(
				imgLeft,
				imgRight,
				disparityMap,
				".\\Reports\\FF_FP_" + to_string(frameNo) + ".csv",
				"",
				&resultBatchFFFP,
				camera.B,
				camera.Lambda);
			
			testService->Reconstruction_FF(
				imgLeft,
				imgRight,
				disparityMap,
				".\\Reports\\FF_" + to_string(frameNo) + ".csv",
				"",
				&resultBatchFF,
				camera.B,
				camera.Lambda);

			testService->Reconstruction_FP(
				imgLeft,
				imgRight,
				disparityMap,
				".\\Reports\\FP_" + to_string(frameNo) + ".csv",
				"",
				&resultBatchFP,
				camera.B,
				camera.Lambda);
			
			testService->Reconstruction_Default(
				imgLeft,
				imgRight,
				disparityMap,
				".\\Reports\\DEFAULT_" + to_string(frameNo) + ".csv",
				"",
				&resultBatchDefault,
				camera.B,
				camera.Lambda);
				
			//system("PAUSE");
			system("cls");
		}

		Export::Csv(resultBatchFFFP, ".\\Reports\\Unstructured2\\resultBatchFFFP.csv");
		Export::Csv(resultBatchFF, ".\\Reports\\Unstructured2\\resultBatchFF.csv");
		Export::Csv(resultBatchFP, ".\\Reports\\Unstructured2\\resultBatchFP.csv");
		Export::Csv(resultBatchDefault, ".\\Reports\\Unstructured2\\resultBatchDefault.csv");
	}

#pragma endregion	

}



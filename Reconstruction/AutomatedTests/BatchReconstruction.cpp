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
			if (i < 3) {
				i++;
				continue;
			}
			int total = paths_base.size();

			cout << "--------------------------------------------------------------------" << endl;
			cout << "Executing: " + path.substr(path.find("s\\") + 2, path.size()) << endl;
			cout << "Progress: " + to_string(i) + " | " + to_string(total) << endl;
			cout << "--------------------------------------------------------------------" << endl << endl << endl << endl;

			string export_path_FFFP = ".\\Reports\\Export_Result\\FF_FP\\" + path.substr(path.find("s\\") + 2, path.size());
			string export_path_FF = ".\\Reports\\Export_Result\\FF\\" + path.substr(path.find("s\\") + 2, path.size());
			string export_path_FP = ".\\Reports\\Export_Result\\FP\\" + path.substr(path.find("s\\") + 2, path.size());
			string export_path_Default = ".\\Reports\\Export_Result\\DEFAULT\\" + path.substr(path.find("s\\") + 2, path.size());

			testService->ReconstructionFF_FP(path + "\\calib.txt",
				path + "\\im0.png",
				path + "\\im1.png",
				path + "\\disp0.pfm",
				export_path_FFFP + "_FF_FP.csv",
				"",
				&resultBatchFFFP);

			testService->Reconstruction_FF(path + "\\calib.txt",
				path + "\\im0.png",
				path + "\\im1.png",
				path + "\\disp0.pfm",
				export_path_FF + "_FF.csv",
				"",
				&resultBatchFF);

			testService->Reconstruction_FP(path + "\\calib.txt",
				path + "\\im0.png",
				path + "\\im1.png",
				path + "\\disp0.pfm",
				export_path_FP + "_FP.csv",
				"",
				&resultBatchFP);

			testService->Reconstruction_Default(path + "\\calib.txt",
				path + "\\im0.png",
				path + "\\im1.png",
				path + "\\disp0.pfm",
				export_path_Default + "_DEF.csv",
				"",
				&resultBatchDefault);

			i++;

			system("cls");
		}

		Export::Csv(resultBatchFFFP, ".\\Reports\\resultBatchFFFP.csv");
		Export::Csv(resultBatchFF, ".\\Reports\\resultBatchFF.csv");
		Export::Csv(resultBatchFP, ".\\Reports\\resultBatchFP.csv");
		Export::Csv(resultBatchDefault, ".\\Reports\\resultBatchDefault.csv");
	}

	void BatchReconstruction::TestHeartDepthMap(string path_calib_left, string path_calib_right, string path_video1, string path_video2, string basePathDepthMap) {
		
		map<string, double> resultBatchFFFP;
		map<string, double> resultBatchFF;
		map<string, double> resultBatchFP;
		map<string, double> resultBatchDefault;
		int count = 0;
		int depthMapCount = -1;
		string pathDepthMap = "";

		PointUtilities *pointUtilities = new PointUtilities();
		AutomatedTests::TestService* testService = new AutomatedTests::TestService();
		vector<Mat> framesLeft = Convert::VideoToFrames(path_video1);
		vector<Mat> framesRight = Convert::VideoToFrames(path_video2);
		CameraProperties camera = Import::HeartCameraParameters(path_calib_left, path_calib_right);
		OpenCV openCv;


		for (int frameNo = 0; frameNo < framesLeft.size(); frameNo++)
		{
			Mat imgLeft = framesLeft[frameNo];
			Mat imgRight = framesRight[frameNo];

			// original round(mod((FrameNo/25 + 0.466667)*30,20))
			depthMapCount = (int)std::round((frameNo / 25.0 + 0.466667) * 30.0) % 20;
			
			StringHelper::Append(pathDepthMap, basePathDepthMap);
			StringHelper::Append(pathDepthMap, to_string(depthMapCount));
			StringHelper::Append(pathDepthMap, ".txt");
			vector<vector<float>> matrizDepthZ = Import::HeartDepthMapFloat(pathDepthMap, 360);
			vector<vector<Point3f>> matrizDepthMat = Import::HeartDepthMap(pathDepthMap, 360);
			float maxDepthMap = pointUtilities->GetMaxAbsCoord(matrizDepthMat, "z");
			float minDepthMap = pointUtilities->GetMinAbsCoord(matrizDepthMat, "z");
			vector<vector<int>> matrizDepthMatNormalizedZ;

			for each (vector<float> row in matrizDepthZ)
			{
				matrizDepthMatNormalizedZ.push_back(vector<int>());

				for each (float z in row)
				{
					matrizDepthMatNormalizedZ[matrizDepthMatNormalizedZ.size() - 1].push_back(((z - minDepthMap) / (minDepthMap - maxDepthMap)) * 255);
				}
			}

			Mat depthMap(288, 360, 1, &matrizDepthMatNormalizedZ);
			
			openCv.ShowImage(depthMap, "Depth Map");

			// Pegar o frame de cada imagem e aplicar o sift/calibração
			// comparar o erro de cada ponto e extrair

			cout << "--------------------------------------------------------------------" << endl;
			cout << "Executing: " + to_string(frameNo) << endl;
			cout << "Progress: " + to_string(frameNo) + " | " + to_string(framesLeft.size()) << endl;
			cout << "--------------------------------------------------------------------" << endl << endl << endl << endl;

			string export_path_FFFP = ".\\Reports\\Export_Result\\FF_FP\\heart_calib.txt";
			string export_path_FF = ".\\Reports\\Export_Result\\FF\\heart_calib.txt";
			string export_path_FP = ".\\Reports\\Export_Result\\FP\\heart_calib.txt";
			string export_path_Default = ".\\Reports\\Export_Result\\DEFAULT\\heart_calib.txt";

			//Reconstruction_Default(Mat img1, Mat img2, Mat depth_map, string path_export_CSV, string path_export_OBJ, map<string, double>* _resultBatch, int calibB, int calibLambda);
			testService->ReconstructionFF_FP(
				imgLeft,
				imgRight,
				depthMap,
				"",
				"",
				&resultBatchFFFP,
				camera.B,
				camera.Lambda);

			testService->Reconstruction_FF(
				imgLeft,
				imgRight,
				depthMap,
				"",
				"",
				&resultBatchFFFP,
				camera.B,
				camera.Lambda);

			testService->Reconstruction_FP(
				imgLeft,
				imgRight,
				depthMap,
				"",
				"",
				&resultBatchFFFP,
				camera.B,
				camera.Lambda);

			testService->Reconstruction_Default(
				imgLeft,
				imgRight,
				depthMap,
				"",
				"",
				&resultBatchFFFP,
				camera.B,
				camera.Lambda);

			system("cls");
		}
	}

#pragma endregion	

}


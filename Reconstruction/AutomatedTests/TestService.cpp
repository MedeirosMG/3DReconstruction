#include "stdafx.h"
#include "TestService.h"

namespace AutomatedTests {

	string path_calib = ".\\Others Files\\Cable-perfect\\calib.txt";
	string path_img1 = ".\\Others Files\\Cable-perfect\\im0.png";
	string path_img2 = ".\\Others Files\\Cable-perfect\\im1.png";
	string path_disparity = ".\\Others Files\\Cable-perfect\\disp0.pfm";
	string path_exportFF = ".\\Others Files\\resultsFF.csv";
	string path_export = ".\\Others Files\\results.csv";
	string path_exportFF_FP = ".\\Others Files\\resultsFF_FP.csv";
	string path_exportFP = ".\\Others Files\\resultsFP.csv";

	string path_unstructured1 = ".\\Others Files\\unstructured01.png";
	string path_unstructured2 = ".\\Others Files\\unstructured02.png";

	TestService::TestService()
	{
		_time = new Time();
	}

	TestService::~TestService()
	{
	}
	
	void TestService::ReconstructionFF_FP()
	{
		cout << "======= Start Test using firefly and sift filter ======= " << endl;

		ControllerService* controller = new ControllerService(path_img1, path_img2);
		controller->SetFireflyProperties(3, 100, 100);
		controller->SetCannyProperties(100, 250, 3);
		controller->SetGeneralProperties();
		controller->SetSiftProperties(0);
		controller->SetCalibrationProperties(path_calib, path_disparity, path_exportFF_FP);
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
		
		cout << "======== End Test ======== " << endl;
	}

	void TestService::Reconstruction_FF()
	{
		cout << "======= Start Test using firefly ======= " << endl;

		ControllerService* controller = new ControllerService(path_img1, path_img2);
		controller->SetFireflyProperties(3, 100, 100);
		controller->SetCannyProperties(100, 250, 3);
		controller->SetGeneralProperties();
		controller->SetSiftProperties(0);
		controller->SetCalibrationProperties(path_calib, path_disparity, path_exportFF);
		controller->SetSiftFilterProperties(20, 500);
		controller->SetVisualizerProperties(false);
		controller->LoadServices();

		controller->FireflyApply();
		controller->CannyApply();
		controller->ConnectedComponentsApply();
		controller->FindRegionsApply();
		controller->SiftOnMaskApply();
		controller->ConvertSiftApply();
		controller->CalibrationApply();
		controller->DelaunayApply();
		controller->RenderApply();

		cout << "======== End Test ======== " << endl;
	}

	void TestService::Reconstruction_FP()
	{
		cout << "======= Start Test using firefly ======= " << endl;

		ControllerService* controller = new ControllerService(path_img1, path_img2);
		controller->SetFireflyProperties(3, 100, 100);
		controller->SetCannyProperties(100, 250, 3);
		controller->SetGeneralProperties();
		controller->SetSiftProperties(0);
		controller->SetCalibrationProperties(path_calib, path_disparity, path_exportFP);
		controller->SetSiftFilterProperties(20, 500);
		controller->SetVisualizerProperties(false);
		controller->LoadServices();

	
		controller->CannyApply();
		controller->SiftApply();
		controller->SiftFilterApply();
		controller->ConvertSiftApply();
		controller->CalibrationApply();
		controller->DelaunayApply();
		controller->RenderApply();

		cout << "======== End Test ======== " << endl;
	}

	void TestService::Reconstruction_Default()
	{
		cout << "======= Start Test using firefly ======= " << endl;

		ControllerService* controller = new ControllerService(path_img1, path_img2);
		controller->SetFireflyProperties(3, 100, 100);
		controller->SetCannyProperties(100, 250, 3);
		controller->SetGeneralProperties();
		controller->SetSiftProperties(0);
		controller->SetCalibrationProperties(path_calib, path_disparity, path_export);
		controller->SetSiftFilterProperties(20, 500);
		controller->SetVisualizerProperties(false);
		controller->LoadServices();

		controller->CannyApply();
		controller->SiftApply();
		controller->ConvertSiftApply();
		controller->CalibrationApply();
		controller->DelaunayApply();
		controller->RenderApply();

		cout << "======== End Test ======== " << endl;
	}

	void TestService::ReconstructionWithTimeExecution()
	{
		string pathFile = ".\\Reports";
		cout << "======= Start Test ======= " << endl;

		ControllerService* controller = new ControllerService(path_unstructured1, path_unstructured2);

		controller->SetFireflyProperties(1, 50, 100);
		controller->SetCannyProperties(50, 700, 3);
		controller->SetGeneralProperties();
		controller->SetSiftProperties(400);
		controller->SetCalibrationProperties(path_calib, path_disparity, path_export);
		controller->SetVisualizerProperties(false);

		_time->Import(pathFile);

		_time->Run(std::bind(&ControllerService::CannyApply, controller), "CannyApply");
		_time->Run(std::bind(&ControllerService::FireflyApply, controller), "FireflyApply");
		_time->Run(std::bind(&ControllerService::ConnectedComponentsApply, controller), "ConnectedComponentsApply");
		_time->Run(std::bind(&ControllerService::FindRegionsApply, controller), "FindRegionsApply");
		_time->Run(std::bind(&ControllerService::SiftApply, controller), "SiftApply");
		_time->Run(std::bind(&ControllerService::ConvertSiftApply, controller), "RansacApply");
		//_time->Run(std::bind(&ControllerService::CalibrationApply, controller), "CalibrationApply");
		_time->Run(std::bind(&ControllerService::DelaunayApply, controller), "DelaunayApply");
		_time->PrintResult();
		_time->Export(pathFile);

		// _time->Run(std::bind(&ControllerService::RenderApply, controller), "RenderApply");

		cout << "======== End Test ======== " << endl;
	}

	void TestService::Delaunay()
	{
		CannyService *canny = new CannyService();
		DelaunayService *teste = new DelaunayService();
		teste->TestExecute(canny->Execute(imread(".\\Others Files\\TestImage.jpg"), 50, 700, 3));
	}

	void TestService::Firefly() 
	{
		FireflyService *test = new FireflyService();
		test->TestExecute(".\\Others Files\\TestImage.jpg", 1, 50, 100);
	}

	void TestService::Render(int argc, char **argv)
	{
		CannyService *canny = new CannyService();
		RenderService *teste = new RenderService();
		teste->TestExecute(&argc, argv);
		//teste->TestExecute(&argc, argv, canny->Execute(imread(".\\Others Files\\TestImage.jpg"), 50, 700, 3));
	}

	void TestService::Canny() 
	{
		CannyService *canny = new CannyService();
		canny->TestExecute(imread(".\\Others Files\\TestImage.jpg"), 50, 700, 3);
	}

	void TestService::Ransac() {

		SiftService *sift = new SiftService();
		RansacService *ransac = new RansacService();
		Mat img1 = imread(".\\Others Files\\im0.png", 0);
		Mat img2 = imread(".\\Others Files\\im1.png", 0);
		
		resize(img1, img1, Size(600, 400));
		resize(img2, img2, Size(600, 400));

		SiftResult sift_result = sift->Execute(img1, img2, 200);
		Mat mask = ransac->FindRansacMask(sift_result, 400);
		vector<DMatch> matchesRansac;
		
		for (int i = 0; i < mask.rows; i++) {
			if ((unsigned int)mask.at<uchar>(i))
				matchesRansac.push_back(sift_result.Matches[i]);
		}
		Mat img;
		drawMatches(img1, sift_result.FirstImageKeyPoints, img2, sift_result.SecondImageKeyPoints, matchesRansac, img);
		imshow("RANSAC", img);
		waitKey();
	}

	void TestService::ConnectedComponents()
	{
		ConnectedComponentsService *CC = new ConnectedComponentsService();
		//Mat img = CC->Execute(imread(".\\Others Files\\im0.png", 0));
		//resize(img, img, Size(800, 600));

		//imshow("Componentes", img);
		//waitKey();
	}

	void TestService::ReconstructionComparison()
	{
		cout << "======= Start Test Reconstruction Comparison ======= " << endl;

		ControllerService* controller = new ControllerService(path_img1, path_img2);
		controller->SetFireflyProperties(3, 100, 100);
		controller->SetCannyProperties(100, 250, 3);
		controller->SetGeneralProperties();
		controller->SetSiftProperties(0);
		controller->SetCalibrationProperties(path_calib, path_disparity, path_export);
		controller->SetSiftFilterProperties(20, 500);
		controller->SetVisualizerProperties(false);
		controller->LoadServices();

		controller->CannyApply();
		controller->SiftApply();
		controller->ConvertSiftApply();
		controller->CalibrationApply();
		controller->DelaunayApply();
		controller->RenderApply();

		cout << "======== End Test ======== " << endl;
	}
	
}


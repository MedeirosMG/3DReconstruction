#include "stdafx.h"
#include "TestService.h"

namespace Services {

	TestService::TestService()
	{
		_time = new Time();
	}

	TestService::~TestService()
	{
	}

	void TestService::Reconstruction(int argc, char **argv)
	{
		cout << "======= Start Test ======= " << endl;

		ControllerService* controller = new ControllerService(".\\Others Files\\im0.png", ".\\Others Files\\im1.png");

		controller->SetFireflyProperties(1, 50, 100);
		controller->SetCannyProperties(50, 700, 3);
		controller->SetConnectedComponentsProperties(128);
		controller->SetGeneralProperties();
		controller->SetSiftProperties(400);
		controller->SetCalibrationProperties(1, 2, 1);
		controller->SetRenderProperties(&argc, argv);
		controller->SetVisuaizerProperties(true);

		controller->CannyApply();
		controller->FireflyApply();	
		controller->ConnectedComponentsApply();
		controller->FindRegionsApply();
		controller->SiftApply();
		controller->RansacApply();
		controller->CalibrationApply();
		controller->DelaunayApply();
		controller->RenderApply();
		
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
		teste->TestExecute(&argc, argv, canny->Execute(imread(".\\Others Files\\TestImage.jpg"), 50, 700, 3));
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

		SiftResult sift_result = sift->Execute(img1, img2, 400);
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
}


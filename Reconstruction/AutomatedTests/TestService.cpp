#include "stdafx.h"
#include "TestService.h"

namespace AutomatedTests {

	TestService::TestService()
	{
		_time = new Time();
	}

	TestService::~TestService()
	{
	}
	
	void TestService::ReconstructionFF_FP(string path_calib, string path_img1, string path_img2, string path_disparity, string path_export)
	{
		cout << "======= Start Test using firefly and sift filter ======= " << endl;

		ControllerService* controller = new ControllerService(path_img1, path_img2);
		controller->SetFireflyProperties(3, 100, 100);
		controller->SetCannyProperties(100, 250, 3);
		controller->SetGeneralProperties();
		controller->SetSiftProperties(0);
		controller->SetCalibrationProperties(path_calib, path_disparity, path_export);
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
		//controller->DelaunayApply();
		//controller->RenderApply();
		
		cout << "======== End Test ======== " << endl;
	}

	void TestService::Reconstruction_FF(string path_calib, string path_img1, string path_img2, string path_disparity, string path_export)
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

		controller->FireflyApply();
		controller->CannyApply();
		controller->ConnectedComponentsApply();
		controller->FindRegionsApply();
		controller->SiftOnMaskApply();
		controller->ConvertSiftApply();
		controller->CalibrationApply();
		//controller->DelaunayApply();
		//controller->RenderApply();

		cout << "======== End Test ======== " << endl;
	}

	void TestService::Reconstruction_FP(string path_calib, string path_img1, string path_img2, string path_disparity, string path_export)
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
		controller->SiftFilterApply();
		controller->ConvertSiftApply();
		controller->CalibrationApply();
		//controller->DelaunayApply();
		//controller->RenderApply();

		cout << "======== End Test ======== " << endl;
	}

	void TestService::Reconstruction_Default(string path_calib, string path_img1, string path_img2, string path_disparity, string path_export)
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
		//controller->DelaunayApply();
		//controller->RenderApply();

		cout << "======== End Test ======== " << endl;
	}

	void TestService::ReconstructionWithTimeExecution(string path_calib, string path_img1, string path_img2, string path_disparity, string path_export)
	{
		string pathFile = ".\\Reports";
		cout << "======= Start Test ======= " << endl;

		ControllerService* controller = new ControllerService(path_img1, path_img2);

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
	
}


// Reconstruction.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Services\ControllerService.h"

using namespace Services;

int main(int argc, char **argv)
{
	cout << "======= Start Test ======= " << endl;

	ControllerService* controller = new ControllerService(".\\Others Files\\TestImage.jpg", ".\\Others Files\\TestImage.jpg");
	
	controller->SetFireflyProperties(1, 50, 100);
	controller->SetCannyProperties(50, 700, 3);
	controller->SetConnectedComponentsProperties(0);
	controller->SetGeneralProperties();
	controller->SetSiftProperties(0);
	controller->SetCalibrationProperties(0, 0, 1);
	controller->SetRenderProperties(&argc, argv);
	controller->SetDelaunayProperties(100);


	//controller->FireflyApply();	
	//controller->DisplayImages();

	/*------------------------------------------------------*/

	//controller->ConnectedComponentsApply();
	//controller->FindRegionsApply();
	//controller->SiftApply();
	//controller->RansacApply();
	//controller->CalibrationApply();
	//controller->CannyApply();
	//controller->DelaunayApply();
	controller->RenderApply();


	//---------- TestsDelauney -----------------
	/*
	CannyService *canny = new CannyService();
	DelaunayService *teste = new DelaunayService();
	teste->TestExecute(canny->Execute(imread(".\\Others Files\\TestImage.jpg"), 50, 700, 3));*/
	
	//---------- TestsFirefly ------------------

	//FireflyService *test = new FireflyService();
	//test->TestExecute(".\\Others Files\\TestImage.jpg", 1, 50, 100);

	cout << "======== End Test ======== " << endl;
	system("pause");
	return 0;
}


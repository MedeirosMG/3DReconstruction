// Reconstruction.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AutomatedTests\BatchReconstruction.h"
#include "Helpers\CameraCapture.h"
#include <string>
#include <iostream>
#include <math.h>
#include "Helpers\Import.h"
#include "Helpers\Convert.h"

using namespace AutomatedTests;
using namespace Helpers;

int main(int argc, char **argv)
{

	BatchReconstruction* batch = new BatchReconstruction();
	batch->TestHeartDepthMap(
		".\\Heart2\\Files\\Left.txt", 
		".\\Heart2\\Files\\Right.txt", 
		".\\Heart2\\Left\\", 
		".\\Heart2\\Right\\",
		".\\Heart2\\Files\\heartDepthMap_", 
		".\\Heart2\\Files\\disparityMap_");
	//batch->Test();
	/*batch->Test();

	map<string, AverageDeviationStd*> resultBatchFFFP;
	Import::CalculateAverage(".\\Reports\\Export_Result\\FF_FP", resultBatchFFFP);
	Export::Csv(resultBatchFFFP, ".\\Reports\\average_FF_FP.csv");

	map<string, AverageDeviationStd*> resultBatchFF;
	Import::CalculateAverage(".\\Reports\\Export_Result\\FF", resultBatchFF);
	Export::Csv(resultBatchFF, ".\\Reports\\average_FF.csv");

	map<string, AverageDeviationStd*> resultBatchFP;
	Import::CalculateAverage(".\\Reports\\Export_Result\\FP", resultBatchFP);
	Export::Csv(resultBatchFP, ".\\Reports\\average_FP.csv");

	map<string, AverageDeviationStd*> resultBatchDefault;
	Import::CalculateAverage(".\\Reports\\Export_Result\\DEFAULT", resultBatchDefault);
	Export::Csv(resultBatchDefault, ".\\Reports\\average_DEFAULT.csv");*/

	/*CameraCapture *camera = new CameraCapture();
	camera->Visualize(true);
	camera->Capture(".\\StructuredImage");*/

	/*TestService* test = new	TestService();
	test->Reconstruction_FP(
		".\\StructuredImage\\abajur1.png",
		".\\StructuredImage\\abajur2.png",
		"",
		"",
		"",
		".\\StructuredImage\\Objetos\\abajur",
		NULL,
		50,
		23
	);*/


	system("pause");
	return 0;
}


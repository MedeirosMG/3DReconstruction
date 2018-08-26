#include "stdafx.h"
#include "FireflyService.h"
#include "../Helpers/Firefly_Optimization.h"
#include "../Helpers/multilimiarizacao.h"
namespace Services {

	FireflyService::FireflyService()
	{
		_openCv = new OpenCV();
	}

	FireflyService::FireflyService(OpenCV * openCv)
	{
		_openCv = openCv;
	}

	FireflyService::~FireflyService()
	{
	}

	Mat FireflyService::Execute(Mat img, int n_thresholds, int n_fireflies, int n_generations)
	{
		std::vector<unsigned int> bests;

		//Find best thresholds with firefly algorithm
		bests = beststhresholds(img, n_thresholds, n_fireflies, n_generations);

		//Paint image using best thresholds
		Mat seg = MultiLim2(img, bests, 0);

		return seg;
	}
}
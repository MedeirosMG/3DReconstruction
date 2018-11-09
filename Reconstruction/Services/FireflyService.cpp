#include "stdafx.h"
#include "FireflyService.h"

namespace Services {

	FireflyService::FireflyService()
	{
		_openCv = new OpenCV();
		_firefly = new Firefly();
		_multiThreshold = new MultiThreshold();
	}

	FireflyService::FireflyService(OpenCV * openCv)
	{
		_openCv = openCv;
		_firefly = new Firefly();
		_multiThreshold = new MultiThreshold();
	}

	FireflyService::~FireflyService()
	{
	}

	Mat FireflyService::Execute(Mat img, int n_thresholds, int n_fireflies, int n_generations)
	{
		std::vector<unsigned int> bests;

		//Convert image to gray
		Mat grayedImg = _openCv->ColorConverter(img, CV_RGB2GRAY);

		//Find best thresholds with firefly algorithm
		bests = _firefly->BestsThresholds(grayedImg, n_thresholds, n_fireflies, n_generations);

		//Paint image using best thresholds
		Mat seg = _multiThreshold->MultiLim2(grayedImg, bests, 0);

		return seg;
	}

	void FireflyService::TestExecute(Mat img, int n_thresholds, int n_fireflies, int n_generations)
	{
		std::vector<unsigned int> bests;

		//Convert image to gray
		Mat grayedImg = _openCv->ColorConverter(img, CV_RGB2GRAY);

		//Find best thresholds with firefly algorithm
		bests = _firefly->BestsThresholds(grayedImg, n_thresholds, n_fireflies, n_generations);

		//Paint image using best thresholds
		Mat seg = _multiThreshold->MultiLim2(grayedImg, bests, 0);

		namedWindow("Firefly Test", 2);

		imshow("Firefly Test", seg);
	}

	void FireflyService::TestExecute(string imgPath, int n_thresholds, int n_fireflies, int n_generations)
	{
		std::vector<unsigned int> bests;

		//Convert image to gray
		Mat grayedImg = _openCv->ReadImage(imgPath);

		grayedImg = _openCv->ColorConverter(grayedImg, CV_RGB2GRAY);

		//Find best thresholds with firefly algorithm
		bests = _firefly->BestsThresholds(grayedImg, n_thresholds, n_fireflies, n_generations);

		//Paint image using best thresholds
		Mat seg = _multiThreshold->MultiLim2(grayedImg, bests, 0);

		namedWindow("Firefly Test", 2);

		imshow("Firefly Test", seg);
	}

}
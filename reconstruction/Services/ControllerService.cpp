#include "stdafx.h"
#include "ControllerService.h"

namespace Services {

	ControllerService::ControllerService()
	{
		_openCv = new OpenCV();
		LoadServices();
	}

	ControllerService::ControllerService(Mat firstImage, Mat secondImage)
	{
		_firstImage = firstImage;
		_secondImage = secondImage;
		_openCv = new OpenCV();
		LoadServices();
	}

	ControllerService::ControllerService(string pathFirstImage, string pathSecondImage)
	{
		_firstImage = imread(pathFirstImage);
		_secondImage = imread(pathSecondImage);
		_openCv = new OpenCV();
		LoadServices();
	}

	ControllerService::~ControllerService()
	{
	}

#pragma region [ Apply ]

	bool ControllerService::CalibrationApply() 
	{		
		try
		{
			//_resultCalibration = _calibrationService->CalculateStereoCameraCalibration(_resultSift);
			_calibrationService->PrintResult(_resultCalibration);
			_calibrationService->OrderPointsByAsc(_resultCalibration);
		}
		catch (const std::exception& ex)
		{
			cout << ">> Error Calibration " << ex.what() << endl;
		}

		return false;
	}

	bool ControllerService::CannyApply() 
	{
		try
		{
			_pointsCanny = _cannyService->Execute(_firstImage, _cannyLowThresh, _cannyHighTresh, _cannyKernelSize);
			return true;
		}
		catch (const std::exception& ex)
		{
			cout << ">> Error Canny " << ex.what() << endl;
			return false;
		}
	}

	bool ControllerService::ConnectedComponentsApply() 
	{
		try
		{
			_InterestRegionsFirstImage = _connectedComponentsService->Execute(_firstImageModified, _connectedComponentsThreshVal);
			_InterestRegionsSecondImage = _connectedComponentsService->Execute(_secondImageModified, _connectedComponentsThreshVal);
			return true;
		}
		catch (const std::exception& ex)
		{
			cout << ">> Error ComponentsConnected " << ex.what() << endl;
			return false;
		}
	}

	bool ControllerService::DelaunayApply() 
	{
		try
		{
			_resultDelaunay = _delaunayService->Execute(_resultCalibration);
			return true;
		}
		catch (const std::exception& ex)
		{
			cout << ">> Error Delaunay " << ex.what() << endl;
			return false;
		}
	}

	bool ControllerService::FindRegionsApply() 
	{
		try
		{
			_firstImageModified = _findRegionsService->Execute(_InterestRegionsFirstImage, _firstImage);
			_secondImageModified = _findRegionsService->Execute(_InterestRegionsSecondImage, _secondImage);
			return true;
		}
		catch (const std::exception& ex)
		{
			cout << ">> Error FindRegions " << ex.what() << endl;
			return false;
		}
	}

	bool ControllerService::RansacApply() 
	{
		try
		{
			//_resultRansac = _ransacService->Execute(_resultSift, _ransacThresh);
		}
		catch (const std::exception& ex)
		{
			cout << ">> Error on Ransac. " << endl << endl << ex.what() << endl;
			return false;
		}
	}

	bool ControllerService::SiftApply() 
	{
		try
		{
			_resultSift = _siftService->Execute(_firstImageModified, _secondImageModified, _siftThreshold);

			return true;
		}
		catch (const std::exception& ex)
		{
			cout << ">> Error on execution of SIFT algorithm. " << endl << endl << ex.what() << endl;
			return false;
		}
	}

	bool ControllerService::RenderApply() 
	{
		try
		{
			_renderService->Execute(_argc, _argv, _resultDelaunay, _resultCalibration);
		}
		catch (const std::exception& ex)
		{
			cout << ">> Error on rendering. " << endl << endl << ex.what() << endl;
			return false;
		}
	}

	bool ControllerService::FireflyApply()
	{
		try
		{
			_firstImageModified = _fireflyService->Execute(_firstImage, _thresholds, _number_fireflies, _number_generations);
			_secondImageModified = _fireflyService->Execute(_secondImage, _thresholds, _number_fireflies, _number_generations);
			return true;
		}
		catch (const std::exception& ex)
		{
			cout << ">> Error on execution of FireFly algorithm. " << endl << endl << ex.what() << endl;
			return false;
		}
	}

	bool ControllerService::ReadImages(string pathFirstImage, string pathSecondImage)
	{
		try
		{
			_firstImage = _inputImageService->Execute(pathFirstImage);
			_secondImage = _inputImageService->Execute(pathSecondImage);

			return true;
		}
		catch (const std::exception& ex)
		{
			cout << "Error Read Images" << ex.what() << endl;
			return false;
		}
	}

#pragma endregion

#pragma region [ Properties ]

	void ControllerService::SetCannyProperties(double cannyLowThresh, double cannyHighTresh, int cannyKernelSize)
	{
		_cannyLowThresh = cannyLowThresh;
		_cannyHighTresh = cannyHighTresh;
		_cannyKernelSize = cannyKernelSize;
	}

	void ControllerService::SetSiftProperties(int siftThreshold = 400)
	{
		_siftThreshold = siftThreshold;
	}

	void ControllerService::SetConnectedComponentsProperties(int connectedComponentsThreshVal)
	{
		_connectedComponentsThreshVal = connectedComponentsThreshVal;
	}

	void ControllerService::SetCalibrationProperties(float calibrationB, float calibrationLambda, int calibrationK)
	{
		_calibrationB = calibrationB;
		_calibrationLambda = calibrationLambda;
		_calibrationK =	calibrationK;
	}

	void ControllerService::SetGeneralProperties()
	{
	}

	void ControllerService::SetFireflyProperties(int thresholds, int number_fireflies, int number_generations)
	{
		_thresholds = thresholds;
		_number_fireflies = number_fireflies;
		_number_generations = number_generations;
	}

	void ControllerService::SetRenderProperties(int *argc, char **argv)
	{
		_argc = argc;
		_argv = argv;
	}

	void ControllerService::SetRansacProperties(double ransacThreshold)
	{
		_ransacThresh = ransacThreshold;
	}

#pragma endregion

	void ControllerService::LoadServices()
	{
		_calibrationService = new CalibrationService(_openCv);
		_cannyService = new CannyService(_openCv);
		_connectedComponentsService = new ConnectedComponentsService(_openCv);
		_delaunayService = new DelaunayService(_openCv);
		_findRegionsService = new FindRegionsService(_openCv);
		_fireflyService = new FireflyService(_openCv);
		_ransacService = new RansacService(_openCv);
		_siftService = new SiftService(_openCv);
		_inputImageService = new InputImageService(_openCv);
		_renderService = new RenderService(_openCv);
	}

	void ControllerService::SaveFirstImage(string Path)
	{
		_openCv->SaveImage(Path, _firstImage);
	}

	void ControllerService::SaveSecondImage(string Path)
	{
		_openCv->SaveImage(Path, _secondImage);
	}

	void ControllerService::SaveFirstImageModified(string Path)
	{
		_openCv->SaveImage(Path, _firstImageModified);
	}

	void ControllerService::SaveSecondImageModified(string Path)
	{
		_openCv->SaveImage(Path, _secondImageModified);
	}

	void ControllerService::DisplayImages() 
	{
		namedWindow("First Image - Original");
		namedWindow("Second Image - Original");
		namedWindow("First Image - Modified");
		namedWindow("Second Image - Modified");

		imshow("First Image - Original", _firstImage);
		imshow("Second Image - Original", _secondImage);
		imshow("First Image - Modified", _firstImageModified);
		imshow("Second Image - Modified", _secondImageModified);

		waitKey();
	}
}
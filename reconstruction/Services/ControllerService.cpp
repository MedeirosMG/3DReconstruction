#include "stdafx.h"
#include "ControllerService.h"

namespace Services {

	ControllerService::ControllerService()
	{
		_openCv = new OpenCV();
		_time = new Time();
		LoadServices();
	}

	ControllerService::ControllerService(Mat firstImage, Mat secondImage)
	{
		resize(firstImage, _firstImage, Size(800, 600));
		resize(secondImage, _secondImage, Size(800, 600));
		_openCv = new OpenCV();

		LoadServices();
	}

	ControllerService::ControllerService(string pathFirstImage, string pathSecondImage)
	{
		resize(imread(pathFirstImage), _firstImage, Size(800, 600));
		resize(imread(pathSecondImage), _secondImage, Size(800, 600));

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
			cout << endl << "=== Init Calibration ===" << endl << endl;
			_resultCalibration = _calibrationService->CalculateStereoCameraCalibration(_resultRansac);
			_calibrationService->OrderPointsByAsc(_resultCalibration);

			_visualizer->Show(_resultCalibration);

			return true;
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
			cout << endl << "=== Init Canny ===" << endl << endl;
			_resultCanny = _cannyService->Execute(_firstImage, _cannyLowThresh, _cannyHighTresh, _cannyKernelSize);

			_visualizer->Show(_resultCanny);

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
			cout << endl << "=== Init Connected Components ===" << endl << endl;
			_InterestRegionsFirstImage = _connectedComponentsService->Execute(_firstImageModified);
			_InterestRegionsSecondImage = _connectedComponentsService->Execute(_secondImageModified);

			_visualizer->Show(_InterestRegionsFirstImage, _visualizerName);
			_visualizer->Show(_InterestRegionsSecondImage, _visualizerName);

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
			cout << endl << "=== Init Delaunay ===" << endl << endl;
			_resultDelaunay = _delaunayService->Execute(_resultCalibration, _resultCanny);

			_visualizer->Show(_resultDelaunay);

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
			cout << endl << "=== Init Find Regions ===" << endl << endl;
			_firstImageModified = _findRegionsService->Execute(_InterestRegionsFirstImage, _firstImage);
			_secondImageModified = _findRegionsService->Execute(_InterestRegionsSecondImage, _secondImage);

			_visualizer->Show(_firstImageModified, _visualizerName);
			_visualizer->Show(_secondImageModified, _visualizerName);

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
			cout << endl << "=== Init Ransac ===" << endl << endl;
			_resultRansac = _ransacService->Execute(_resultSift, _ransacThresh);

			_visualizer->Show(_resultRansac);

			return true;
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
			cout << endl << "=== Init Sift ===" << endl << endl;
			_resultSift = _siftService->Execute(_firstImageModified, _secondImageModified, _siftThreshold);

			_visualizer->Show(_resultSift);

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
			cout << endl << "=== Init Rendering ===" << endl << endl;
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
			cout << endl << "=== Init Firefly ===" << endl << endl;
			_firstImageModified = _fireflyService->Execute(_firstImage, _thresholds, _number_fireflies, _number_generations);
			_secondImageModified = _fireflyService->Execute(_secondImage, _thresholds, _number_fireflies, _number_generations);

			_visualizer->Show(_firstImageModified, _visualizerName);
			_visualizer->Show(_secondImageModified, _visualizerName);

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
			cout << endl << "=== Reading Images ===" << endl << endl;
			_firstImage = _inputImageService->Execute(pathFirstImage);
			_secondImage = _inputImageService->Execute(pathSecondImage);

			_visualizer->Show(_firstImage, _visualizerName);
			_visualizer->Show(_secondImage, _visualizerName);

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

	void ControllerService::SetVisualizerProperties(bool execute, string nameWindow)
	{
		_visualizer->SetExecute(execute);

		// Default name
		_visualizerName = nameWindow;

		// Init window
		if(execute)
			_visualizer->NewWindow(_visualizerName);
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
		_renderService = new RenderService(_openCv);
		_visualizer = new Visualizer(_openCv);
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
		Mat tempFirstImage, tempSecondImage, tempFirstImageModified, tempSecondImageModified;

		resize(_firstImage, tempFirstImage, Size(800, 600));
		resize(_secondImage, tempSecondImage, Size(800, 600));
		resize(_firstImageModified, tempFirstImageModified, Size(800, 600));
		resize(_secondImageModified, tempSecondImageModified, Size(800, 600));

		_visualizer->NewWindow("First Image - Original");
		_visualizer->NewWindow("Second Image - Original");
		_visualizer->NewWindow("First Image - Modified");
		_visualizer->NewWindow("Second Image - Modified");

		_visualizer->Show(tempFirstImage, "First Image - Original");
		_visualizer->Show(tempSecondImage, "Second Image - Original");
		_visualizer->Show(tempFirstImageModified, "First Image - Modified");
		_visualizer->Show(tempSecondImageModified, "Second Image - Modified");
	}
}
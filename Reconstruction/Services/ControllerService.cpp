#include "stdafx.h"
#include "ControllerService.h"

namespace Services {

	ControllerService::ControllerService()
	{
		_openCv = new OpenCV();
		_time = new Time();
	}

	ControllerService::ControllerService(map<string, double>* resultBatch)
	{
		_openCv = new OpenCV();
		_time = new Time();

		_resultBatch = resultBatch;
	}

	ControllerService::ControllerService(Mat firstImage, Mat secondImage, map<string, double>* resultBatch)
	{
		_openCv = new OpenCV();

		_firstImage = _openCv->Resize(firstImage, _screenSize);
		_secondImage = _openCv->Resize(secondImage, _screenSize);

		_resultBatch = resultBatch;
	}

	ControllerService::ControllerService(string pathFirstImage, string pathSecondImage, map<string, double>* resultBatch)
	{
		_openCv = new OpenCV();

		_firstImage = _openCv->Resize(_openCv->ReadImage(pathFirstImage), _screenSize);
		_secondImage = _openCv->Resize(_openCv->ReadImage(pathSecondImage), _screenSize);

		_resultBatch = resultBatch;
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
			_resultCalibration = _calibrationService->CalculateStereoCameraCalibration(_resultRansac, _resultCannyDilated);
			_calibrationService->OrderPointsByAsc(_resultCalibration);
			
			_visualizer->Show(_resultCalibration);

			if(_pathExportCSV != "")
				_reconstructionCompareService->Execute(_resultCalibration, _calibration, _pathDisparity, _pathExportCSV, _resultBatch);

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

			cout << endl << "=== Init Canny Dilated ===" << endl << endl;
			_resultCannyDilated = _cannyService->ExecuteDilated(_firstImage, _cannyLowThresh, _cannyHighTresh, _cannyKernelSize);
			_visualizer->Show(_resultCannyDilated, _visualizerName);

			return true;
		}
		catch (const std::exception& ex)
		{
			cout << ">> Error Canny " << ex.what() << endl;
			return false;
		}
	}

	bool ControllerService::ConnectedCannyApply() 
	{
		try
		{
			cout << endl << "=== Init Connected Components on Canny ===" << endl << endl;
			_resultCanny = _connectedComponentsService->ExecuteOnCanny(_resultCannyDilated);
			_visualizer->Show(_resultCanny);
			_resultCannyDilated = _connectedComponentsService->ExecuteOnCannyDilated(_resultCannyDilated);
			_visualizer->Show(_resultCannyDilated, _visualizerName);
			
			return true;
		}
		catch (const std::exception& ex)
		{
			cout << ">> Error ComponentsConnected " << ex.what() << endl;
			return false;
		}
	}

	bool ControllerService::ConnectedComponentsApply()
	{
		try
		{
			cout << endl << "=== Init Connected Components on Canny ===" << endl << endl;
			_InterestRegionsFirstImage = _connectedComponentsService->Execute(_firstImageModified);
			_InterestRegionsSecondImage = _connectedComponentsService->Execute(_secondImageModified);

			for (int i = 0; i < _InterestRegionsFirstImage.size(); i++) {
				_visualizer->Show(_InterestRegionsFirstImage[i], _visualizerName);
				_visualizer->Show(_InterestRegionsSecondImage[i], _visualizerName);
			}


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
			_resultDelaunay = _delaunayService->Execute(_resultCalibration, _resultCanny, _resultCannyDilated,_screenSize);
			//_visualizer->Show(_resultDelaunay); // Implementar show

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
			_InterestRegionsFirstImage = _findRegionsService->Execute(_InterestRegionsFirstImage, _firstImage);
			_InterestRegionsSecondImage = _findRegionsService->Execute(_InterestRegionsSecondImage, _secondImage);

			for (int i = 0; i < _InterestRegionsFirstImage.size(); i++) {
				_visualizer->Show(_InterestRegionsFirstImage[i], _visualizerName);
				_visualizer->Show(_InterestRegionsSecondImage[i], _visualizerName);
			}

			return true;
		}
		catch (const std::exception& ex)
		{
			cout << ">> Error FindRegions " << ex.what() << endl;
			return false;
		}
	}

	bool ControllerService::ConvertSiftApply()
	{
		try
		{
			PointUtilities *utilities = new PointUtilities();
			cout << endl << "=== Init Ransac ===" << endl << endl;

			_resultRansac = utilities->MergePoints(_resultRansac, _ransacService->Execute(_resultSift, _ransacThresh));
			for (int i = 0; i < _resultSiftOnMask.size(); i++) {
				_resultRansac = utilities->MergePoints(_resultRansac, _ransacService->Execute(_resultSiftOnMask[i], _ransacThresh));

			}
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

			_resultSift = _siftService->Execute(_firstImage, _secondImage, _siftThreshold);
			_visualizer->Show(_resultSift, _visualizerName);

			return true;
		}
		catch (const std::exception& ex)
		{
			cout << ">> Error on execution of SIFT algorithm. " << endl << endl << ex.what() << endl;
			return false;
		}
	}

	bool ControllerService::SiftOnMaskApply()
	{
		try
		{
			cout << endl << "=== Init Sift ===" << endl << endl;
			for (int i = 0; i < _InterestRegionsFirstImage.size(); i++) {
				_resultSiftOnMask.push_back(_siftService->Execute(_InterestRegionsFirstImage[i], _InterestRegionsSecondImage[i], _siftThreshold));
				_visualizer->Show(_resultSiftOnMask[i], _visualizerName);
			}

			return true;
		}
		catch (const std::exception& ex)
		{
			cout << ">> Error on execution of SIFT algorithm. " << endl << endl << ex.what() << endl;
			return false;
		}
		
	}

	bool ControllerService::SiftFilterApply()
	{
		try
		{
			PointUtilities utilities;
			cout << endl << "=== Init SiftFilter ===" << endl << endl;
			_resultSift = utilities.FilterKeyPoints(_resultSift, _minY, _minDist, _firstImage, _secondImage);

			_visualizer->Show(_resultSift, _visualizerName);

			return true;
		}
		catch (const std::exception& ex)
		{
			cout << ">> Error on execution of SIFT algorithm. " << endl << endl << ex.what() << endl;
			return false;
		}
	}

	bool ControllerService::SiftOnMaskFilterApply()
	{
		try
		{
			PointUtilities utilities;
			cout << endl << "=== Init SiftFilter ===" << endl << endl;
			for (int i = 0; i < _InterestRegionsFirstImage.size(); i++) {
				_resultSiftOnMask[i] = utilities.FilterKeyPoints(_resultSiftOnMask[i], _minY, _minDist, _InterestRegionsFirstImage[i], _InterestRegionsSecondImage[i]);
				_visualizer->Show(_resultSiftOnMask[i], _visualizerName);
			}

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
			_renderServiceVTK->Execute(_resultDelaunay, _resultCalibration, _resultCanny, _pathExportOBJ);

			return true;
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

	void ControllerService::SetSiftFilterProperties(int minY, int minDist)
	{
		_minDist = minDist;
		_minY = minY;
	}

	void ControllerService::SetCalibrationProperties(float calibrationB, float calibrationLambda, int calibrationK)
	{
		_calibration.B = calibrationB;
		_calibration.Lambda = calibrationLambda;
	}

	void ControllerService::SetCalibrationProperties(string path, string pathDisparity)
	{
		CameraProperties cameraProperties = Import::CameraParameters(path);

		_calibration = cameraProperties;

		_pathDisparity = pathDisparity;
	}

	void ControllerService::SetCalibrationProperties(string path, Mat depthMap)
	{
		CameraProperties cameraProperties = Import::CameraParameters(path);

		_calibration = cameraProperties;

		_depthMap = depthMap;
	}

	void ControllerService::SetCalibrationProperties(float calibrationB, float calibrationLambda, Mat depthMap)
	{
		_calibration.B = calibrationB;
		_calibration.Lambda = calibrationLambda;

		_depthMap = depthMap;
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

	void ControllerService::SetRansacProperties(double ransacThreshold)
	{
		_ransacThresh = ransacThreshold;
	}

	void ControllerService::SetVisualizerProperties(bool execute, string nameWindow)
	{
		_visualizer->SetExecute(execute);

		// Default name
		_visualizerName = nameWindow;
		_visualizerExecute = execute;

		// Init window
		if(execute)
			_visualizer->NewWindow(_visualizerName);
	}

	void ControllerService::SetExportProperties(string pathExportCSV, string pathExportOBJ)
	{
		_pathExportCSV = pathExportCSV;
		_pathExportOBJ = pathExportOBJ;
	}

	void ControllerService::SetScreenProperties(Size imgSize)
	{
		_screenSize = imgSize;

		_firstImage = _openCv->Resize(_firstImage, _screenSize);
		_secondImage = _openCv->Resize(_secondImage, _screenSize);
	}

#pragma endregion

	void ControllerService::LoadServices()
	{
		_calibrationService = new CalibrationService(_calibration.B, _calibration.Lambda, new OpenCV(), _calibration.K, _screenSize);
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
		_renderServiceVTK = new RenderServiceVtk();
		_visualizer = new Visualizer(_visualizerName, _openCv, _visualizerExecute);
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
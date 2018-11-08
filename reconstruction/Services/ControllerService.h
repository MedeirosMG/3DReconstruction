#ifndef SERVICES_RECONSTRUCTION
#define SERVICES_RECONSTRUCTION

#pragma region [ Services ]

#include "CalibrationService.h"
#include "CannyService.h"
#include "ConnectedComponentsService.h"
#include "DelaunayService.h"
#include "FindRegionsService.h"
#include "FireflyService.h"
#include "RansacService.h"
#include "SiftService.h"
#include "InputImageService.h"
#include "RenderService.h"
#include "ReconstructionCompareService.h"
#include "..\Helpers\Console.h"
#include "..\Helpers\Convert.h"
#include "..\Helpers\Visualizer.h"
#include "..\Helpers\Time.h"
#include "..\Helpers\ReconstructionDefine.h"
#include "..\Services\RenderServiceVtk.h"


#pragma endregion

using namespace Helpers;

namespace Services {

	class ControllerService
	{

	private:

		// Algorithms
		OpenCV * _openCv;
		
		// Time Execution
		Time * _time;

		// Services
		CalibrationService* _calibrationService;
		CannyService* _cannyService;
		ConnectedComponentsService* _connectedComponentsService;
		DelaunayService* _delaunayService;
		FindRegionsService* _findRegionsService;
		FireflyService* _fireflyService;
		RansacService* _ransacService;
		SiftService* _siftService;
		InputImageService* _inputImageService;
		RenderService* _renderService;
		RenderServiceVtk* _renderServiceVTK;
		ReconstructionCompareService* _reconstructionCompareService;

		// Utilities
		Visualizer* _visualizer = new Visualizer();

		// General Properties
		Mat _firstImage;
		Mat _secondImage;
		Mat _firstImageModified;
		Mat _secondImageModified;
		Size _screenSize = Size(REC_SCREEN_DEFAULT_WIDTH, REC_SCREEN_DEFAULT_HEIGHT);

		// Delaunay Properties
		vector<Vec<Point3f, 4>> _resultDelaunay;

		// Sift Properties
		int _siftThreshold;
		int _minDist;
		int _minY;
		SiftResult _resultSift;
		vector<SiftResult> _resultSiftOnMask;

		//Ransac Properties
		vector<PointPair> _resultRansac;
		double _ransacThresh;

		// Canny Properties
		double _cannyLowThresh;
		double _cannyHighTresh;
		int _cannyKernelSize;
		vector<Point3f> _resultCanny;
		Mat _resultCannyDilated;

		// Connected Components Properties
		vector<Mat> _InterestRegionsFirstImage;
		vector<Mat> _InterestRegionsSecondImage;
		
		// Calibration Properties
		float _calibrationB;
		float _calibrationLambda;
		int _calibrationK;
		string _pathDisparity;
		string _pathExport;
		bool _exportCalib;
		vector<Point3f> _resultCalibration;

		// Fireflies Properties
		int _thresholds;
		int _number_fireflies;
		int _number_generations;

		// Render Properties
		int *_argc;
		char **_argv;

		// Visualizer properties
		string _visualizerName;
		bool _visualizerExecute;

	public:
		ControllerService();
		ControllerService(Mat firstImage, Mat secondImage);
		ControllerService(string pathFirstImage, string pathSecondImage);
		~ControllerService();

		bool CalibrationApply();
		bool CannyApply();
		bool ConnectedComponentsApply();
		bool ConnectedCannyApply();
		bool DelaunayApply();
		bool FindRegionsApply();
		bool ConvertSiftApply();
		bool SiftApply();
		bool SiftOnMaskApply();
		bool SiftFilterApply();
		bool SiftOnMaskFilterApply();
		bool RenderApply();
		bool FireflyApply();
		bool ReadImages(string pathFirstImage, string pathSecondImage);

		void SetCannyProperties(double cannyLowThresh, double cannyHighTresh, int cannyKernelSize);
		void SetSiftProperties(int siftThreshold);
		void SetSiftFilterProperties(int minY, int minDist);
		void SetCalibrationProperties(string _pathDisparity, string _pathExport, float calibrationB = 0, float calibrationLambda = 0, int calibrationK = 0, bool _export = false);
		void SetCalibrationProperties(string path, string pathDisparity, string pathExport, bool _export = false);
		void SetGeneralProperties();
		void SetFireflyProperties(int thresholds, int number_fireflies, int number_generations);
		void SetRenderProperties(int *argc, char **argv);
		void SetRansacProperties(double ransacThreshold);
		void SetVisualizerProperties(bool execute, string nameWindow = "Default Name");
		void SetScreenProperties(Size screenSize);
		void LoadServices();

		void SaveFirstImage(string Path = ".\\Others Files\\FirstImage.jpg");
		void SaveSecondImage(string Path = ".\\Others Files\\SecondImage.jpg");
		void SaveFirstImageModified(string Path = ".\\Others Files\\FirstImageModified.jpg");
		void SaveSecondImageModified(string Path = ".\\Others Files\\SecondImageModified.jpg");

		void DisplayImages();
	};

}

#endif
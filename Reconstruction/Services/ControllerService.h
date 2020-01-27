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
		map<string, double>* _resultBatch = NULL;

		// Delaunay Properties
		vector<Vec<Point3f, 4>> _resultDelaunay;

		// Sift Properties
		int _siftFeatures;
		int _siftLayers;
		double _siftContrastThresh;
		double _siftEdgeThresh;
		double _siftSigma;
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
		CameraProperties _calibration;
		string _pathDisparity;
		Mat _depthMap;
		bool _exportCalib;
		vector<Point3f> _resultCalibration;

		// Fireflies Properties
		int _thresholds;
		int _number_fireflies;
		int _number_generations;

		// Visualizer properties
		string _visualizerName;
		bool _visualizerExecute;

		// Export properties
		string _pathExportCSV = "";
		string _pathExportOBJ = "";

	public:
		ControllerService();
		ControllerService(map<string, double>* resultBatch);
		ControllerService(Mat firstImage, Mat secondImage, map<string, double>* resultBatch = NULL);
		ControllerService(string pathFirstImage, string pathSecondImage, map<string, double>* resultBatch = NULL);
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
		void SetSiftProperties(int features = 0, int layers = 3, double contrast = 0.04, double edge = 10.0, double sigma = 1.6);
		void SetSiftFilterProperties(int minY, int minDist);
		void SetCalibrationProperties(float calibrationB = 0, float calibrationLambda = 0, int calibrationK = 0);
		void SetCalibrationProperties(string path, string pathDisparity);
		void SetCalibrationProperties(string path, Mat depthMap);
		void SetCalibrationProperties(float calibrationB, float calibrationLambda, Mat depthMap);
		void SetGeneralProperties();
		void SetFireflyProperties(int thresholds, int number_fireflies, int number_generations);
		void SetRansacProperties(double ransacThreshold);
		void SetVisualizerProperties(bool execute, string nameWindow = "Default Name");
		void SetExportProperties(string pathExportCSV = "", string pathExportOBJ = "");
		void SetScreenProperties(Size screenSize);
		void LoadServices();

		void SaveFirstImage(string path = ".\\Others Files\\FirstImage.jpg");
		void SaveSecondImage(string path = ".\\Others Files\\SecondImage.jpg");
		void SaveFirstImageModified(string path = ".\\Others Files\\FirstImageModified.jpg");
		void SaveSecondImageModified(string path = ".\\Others Files\\SecondImageModified.jpg");

		void DisplayImages();
	};

}

#endif
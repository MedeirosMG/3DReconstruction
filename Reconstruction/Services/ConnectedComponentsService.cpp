#include "stdafx.h"
#include "ConnectedComponentsService.h"

namespace Services {

	// ----------- Private

	vector<vector<Point>> ConnectedComponentsService::Filter(vector<vector<Point>> contours)
	{
		if (_threshold == 0.0)
			return contours;

		vector<vector<Point>> result;
		Console::Print(contours);
		double areaScreen = GetBestAverage(contours);

		for each (vector<Point> vecPoint in contours)
		{
			double areaPoints = PointUtilities().GetArea(vecPoint);

			if ((areaPoints / areaScreen >= _threshold) || areaPoints == 0.0)
				result.push_back(vecPoint);
		}

		cout << "Initial size: " << contours.size() << " | End Size: " << result.size() << endl;

		return result;
	}

	double ConnectedComponentsService::GetBestAverage(vector<vector<Point>> contours)
	{
		double result = 0.0;
		int i = _interval;
		double sum = 0.0;
		vector<double> listAreas;
		vector<double> listAverageAreas;

		for each (vector<Point> vecPoint in contours)
		{
			double areaPoints = PointUtilities().GetArea(vecPoint);
			if(areaPoints != 0.0 )
				listAreas.push_back(areaPoints);
		}

		if (i != 0) {
			double acc = 0.0;

			for each (double value in listAreas)
			{
				if (i > 0) {
					acc += value;
					i--;
				}
				else {
					listAverageAreas.push_back(acc / _interval);
					acc = 0.0;
					i = _interval;
				}
			}
		}
		else {
			listAverageAreas = listAreas;
		}

		for each (double value in listAverageAreas)
		{
			sum += value;
		}

		result = sum / listAverageAreas.size();

		return result;
	}


	// ----------- Public

	ConnectedComponentsService::ConnectedComponentsService()
	{
		_openCv = new OpenCV();
	}

	ConnectedComponentsService::ConnectedComponentsService(OpenCV * openCV)
	{
		_openCv = openCV;
	}

	ConnectedComponentsService::ConnectedComponentsService(OpenCV* openCV, Size imgSize, float threshold, float interval)
	{
		_openCv = openCV;
		_screenSize = imgSize;
		_threshold = threshold;
		_interval = interval;
	}

	ConnectedComponentsService::ConnectedComponentsService(OpenCV* openCV, Size imgSize)
	{
		_openCv = openCV;
		_screenSize = imgSize;
	}

	ConnectedComponentsService::~ConnectedComponentsService()
	{
	}

	Mat ConnectedComponentsService::Execute(Mat img)
	{
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;

		findContours(img, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
		//contours = _openCv->ConnectedComponentsAlgorithm(img, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

		Mat result = Mat::zeros(img.size(), CV_8UC3);

		// Applying filter
		contours = Filter(contours);

		if (!contours.empty() && !hierarchy.empty())
		{
			// iterate through all the top-level contours,
			// draw each connected component with its own random color
			int idx = 0;
			for (; idx >= 0; idx = hierarchy[idx][0])
			{
				Scalar color((rand() & 255), (rand() & 255), (rand() & 255));
				drawContours(result, contours, idx, color, CV_FILLED, 8, hierarchy);
				//result = _openCv->DrawContour(contours, idx, color, CV_FILLED, 8, hierarchy);
			}
		}

		return result;
	}

}
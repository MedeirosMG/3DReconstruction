#include "stdafx.h"
#include "ConnectedComponentsService.h"

namespace Services {

	// ----------- Private

	Mat ConnectedComponentsService::DrawFiltering(vector<vector<Point>>& contours, vector<Vec4i>& hierarchy, Mat image)
	{
		Mat result = Mat::zeros(image.size(), CV_8UC3);

		if (!contours.empty() && !hierarchy.empty())
		{
			// iterate through all the top-level contours,
			// draw each connected component with its own random color
			int idx = 0;
			double areaScreen = 0.0;
			double areaPoints = 0.0;
			int countFilter = 0;

			if (_threshold > 0.0)
				areaScreen = GetBestAverage(contours);

			for (; idx >= 0; idx = hierarchy[idx][0])
			{
				if(_threshold > 0.0)
					areaPoints = PointUtilities().GetArea(contours[idx]);

				if ((areaPoints / areaScreen >= _threshold) || areaPoints == 0.0 || _threshold == 0.0) {
					Scalar color((rand() & 255), (rand() & 255), (rand() & 255));
					_openCv->DrawContour(result, contours, idx, color, CV_FILLED, 8, hierarchy);
					countFilter++;
				}
			}

			//cout << "Initial size: " << contours.size() << " | End Size: " << countFilter << endl;
		}

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
			if (areaPoints != 0.0)
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

		// Applying Connected Components from Open CV
		_openCv->ConnectedComponentsAlgorithm(img, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

		// Applying filter
		return DrawFiltering(contours, hierarchy, img);
	}

}
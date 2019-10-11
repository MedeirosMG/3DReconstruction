#include "stdafx.h"
#include "ConnectedComponentsService.h"

bool comp(double a, double b) {
	return a > b;
}

namespace Services {

	// ----------- Private

	Mat ConnectedComponentsService::DrawFiltering(vector<vector<Point>>& contours, vector<Vec4i>& hierarchy, Mat image, int n)
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
			vector<double> areas;
			for (; idx >= 0; idx = hierarchy[idx][0])
			{
				areaPoints = PointUtilities().GetArea(contours[idx]);
				areas.push_back(areaPoints);
			}
			sort(areas.begin(), areas.end(), comp);
			idx = 0;
			for (; idx >= 0; idx = hierarchy[idx][0])
			{
				areaPoints = PointUtilities().GetArea(contours[idx]);
				for (int i = 0; i < n; i++) {
					if (areaPoints == areas[i]) {
						Scalar color((rand() & 255), (rand() & 255), (rand() & 255));
						_openCv->DrawContour(result, contours, idx, color, CV_FILLED, 8, hierarchy);
					}
				}
			}
			/*
			for (; idx >= 0; idx = hierarchy[idx][0])
			{
				if(_threshold > 0.0)
					areaPoints = PointUtilities().GetArea(contours[idx]);
				if ((areaPoints / areaScreen >= _threshold) || areaPoints == 0.0 || _threshold == 0.0) {
					Scalar color((rand() & 255), (rand() & 255), (rand() & 255));
					_openCv->DrawContour(result, contours, idx, color, CV_FILLED, 8, hierarchy);
					countFilter++;
				}
			}*/

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

	vector<Mat> ConnectedComponentsService::Execute(Mat img)
	{
				
		vector<uchar> cores;
		int a;
		for (int y = 0; y < img.rows; y++) {
			for (int x = 0; x < img.cols; x++)
			{
				for (a = 0; a < cores.size(); a++)
					if (img.at<uchar>(y, x) == cores[a])
						break;
				if (a == cores.size() && img.at<uchar>(y, x) != 0)
					cores.push_back(img.at<uchar>(y, x));
			}
		}
		vector<Mat> regions;
		vector<Mat> resultRegions;
		for (int i = 0; i < cores.size(); i++) {
			Mat reg(img.rows, img.cols, img.type());
			regions.push_back(reg);
		}
		
		for (int y = 0; y < img.rows; y++) {
			for (int x = 0; x < img.cols; x++)
			{
				for (int i = 0; i < cores.size(); i++) {
					if (img.at<uchar>(y, x) == cores[i])
						regions[i].at<uchar>(y, x) = 255;
					else
						regions[i].at<uchar>(y, x) = 0;

				}
			}
		}
		for (int i = 0; i < regions.size(); i++) {
			vector<vector<Point>> contours;
			vector<Vec4i> hierarchy;

			_openCv->ConnectedComponentsAlgorithm(regions[i], contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
			resultRegions.push_back(DrawFiltering(contours, hierarchy, img, 5));
			resultRegions[i] = _openCv->Dilate(resultRegions[i], 2);
		}
		



		// Applying Connected Components from Open CV

		// Applying filter
		return resultRegions;
	}
	vector<Point3f>  ConnectedComponentsService::ExecuteOnCanny(Mat img)
	{

		Mat ret;
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;

		_openCv->ConnectedComponentsAlgorithm(img, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
		ret = DrawFiltering(contours, hierarchy, img, 2);
		//ret = _openCv->Erode(ret, 2);

		vector<Point3f> result;
		vector<cv::Point> locations;
		for (int j = 0; j< ret.rows; j++) {
			for (int i = 0; i< ret.cols; i++) {
				if (ret.at<uchar>(j, i) != 0) {
					cv::Point temp;
					temp.x = i;
					temp.y = j;
					locations.push_back(temp);
				}
			}
		}

		//Push on result vector the points that will actually be used on delauney
		for (int i = 0; i < locations.size(); i += 10) {
			Point3f temp(locations[i].x, locations[i].y, 0);
			result.push_back(temp);
		}


		// Applying Connected Components from Open CV

		// Applying filter
		return result;
	}

	Mat ConnectedComponentsService::ExecuteOnCannyDilated(Mat img)
	{
		Mat ret;
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;

		_openCv->ConnectedComponentsAlgorithm(img, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
		ret = DrawFiltering(contours, hierarchy, img, 1);
		//ret = _openCv->Erode(ret, 2);


		// Applying Connected Components from Open CV

		// Applying filter
		return ret;
	}

}
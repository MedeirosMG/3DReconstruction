#include "stdafx.h"
#include "CannyService.h"

namespace Services {

	CannyService::CannyService()
	{
		_openCv = new OpenCV();
	}

	CannyService::CannyService(OpenCV* openCv)
	{
		_openCv = openCv;
	}


	CannyService::~CannyService()
	{
	}

	Mat CannyService::ExecuteDilated(const Mat inputImage, double lowThresh, double highThresh, int kernelSize)
	{
		Mat contours = _openCv->CannyAlgorithm(inputImage, lowThresh, highThresh, kernelSize);
		Mat contoursDilated = _openCv->Dilate(contours, 2);

		return contoursDilated;
	}

	vector<Point3f> CannyService::Execute(const Mat inputImage, double lowThresh, double highThresh, int kernelSize)
	{
		vector<Point3f> result;
		vector<cv::Point> locations;

		//Apply canny
		Mat contours = _openCv->CannyAlgorithm(inputImage, lowThresh, highThresh, kernelSize);
		
		//Find non black points
		for (int j = 0; j< contours.rows; j++) {
			for (int i = 0; i< contours.cols; i++) {
				if (contours.at<uchar>(j, i) > 0) {
					cv::Point temp;
					temp.x = i;
					temp.y = j;
					locations.push_back(temp);
				}
			}
		}

		//Push on result vector the points that will actually be used on delauney
		for (int i = 0; i < locations.size(); i++) {
			Point3f temp(locations[i].x, locations[i].y, 0);
			result.push_back(temp);
		}

		return result;
	}

	void CannyService::TestExecute(const Mat inputImage, double lowThresh, double highThresh, int kernelSize)
	{
		//Apply canny
		Mat contours = _openCv->CannyAlgorithm(inputImage, lowThresh, highThresh, kernelSize);

		namedWindow("TestCanny", 2);
		imshow("TestCanny", contours);

		waitKey();
	}
}
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

	vector<Entities::CustomPoint> CannyService::Execute(const Mat inputImage, double lowThresh, double highThresh, int kernelSize)
	{
		vector<Entities::CustomPoint> result;
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
		for (int i = 0; i < locations.size(); i = i + 3) {
			Entities::CustomPoint temp(-4.0 + (locations[i].x / (contours.cols / 8.0)), 4.0 - (locations[i].y / (contours.rows / 8.0)), 0);
			result.push_back(temp);
		}

		return result;
	}

	void CannyService::TestExecute(const Mat inputImage, double lowThresh, double highThresh, int kernelSize)
	{
		vector<Entities::CustomPoint> result;
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
		for (int i = 0; i < locations.size(); i = i + 3) {
			Entities::CustomPoint temp(-4.0 + (locations[i].x / (contours.cols / 8.0)), 4.0 - (locations[i].y / (contours.rows / 8.0)), 0);
			result.push_back(temp);
		}
		
		Mat newImage = Mat(contours.rows, contours.cols, CV_8U, Scalar(0));

		for each (Entities::CustomPoint var in result)
		{
			newImage.at<uchar>(var.X, var.Y) = 255;
		}

		namedWindow("TestCanny", 2);
		imshow("TestCanny", newImage);

		waitKey();
	}
}
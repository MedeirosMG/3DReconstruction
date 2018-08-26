#include "stdafx.h"
#include "OpenCV.h"

namespace Algorithms {

	OpenCV::OpenCV()
	{
		line_color = Scalar(15.0, 100.0, 15.0);
	}

	OpenCV::~OpenCV()
	{

	}

	//Canny function
	Mat OpenCV::CannyAlgorithm(Mat img, double lowThresh, double highThresh, int kernelSize)
	{
		Mat ret;
		Canny(img, ret, lowThresh, highThresh, kernelSize);
		return ret;
	}

	//Read a single image
	Mat OpenCV::ReadImage(string path)
	{
		Mat result;

		result = imread(path);

		if(!result.data)
			throw std::exception("Error! Image could not be read.");
			
		return result;	
	}

	//Convert the colors of an image
	Mat OpenCV::ColorConverter(Mat image, int cvEnum)
	{
		Mat result;
		cvtColor(image, result, cvEnum);

		return result;  
	}

	//Connected components (find regions)
	vector<vector<Point>> OpenCV::ConnectedComponentsAlgorithm(Mat inputImage, vector<Vec4i> hierarchy, int cvMode, int cvMethod)
	{
		vector<vector<Point>> resultContours;
		findContours(inputImage, resultContours, hierarchy, cvMode, cvMethod);

		return resultContours;
	}
	
	//Draw the contours of an image
	Mat OpenCV::DrawContour(vector<vector<Point>> contours, int indice, Scalar color, int mode, int lineType, vector<Vec4i> hierarchy)
	{
		Mat result;
		drawContours(result, contours, indice, color, mode, lineType, hierarchy);

		return result;
	}	

	//SIFT detector component
	vector<KeyPoint> OpenCV::SiftDetector(cv::SiftFeatureDetector* detector, Mat img)
	{
		vector<KeyPoint> result;

		detector->detect(img, result);

		return result;
	}

	//SIFT descriptor component
	Mat OpenCV::SiftDescriptor(Mat imgInput, vector<KeyPoint> keypoints)
	{
		Mat result;
		cv::SiftDescriptorExtractor descriptor;
		descriptor.compute(imgInput, keypoints, result);

		return result;
	}
	
	//Brute Force Matcher for found points
	vector<DMatch> OpenCV::BFMatcher(Mat img1, Mat img2)
	{
		vector<DMatch> result;
		cv::BFMatcher bf;

		bf.match(img1, img2, result);

		return result;
	}

	//Draw line in image openCv
	void OpenCV::DrawLine(cv::Mat image, const cv::Point& p1, const cv::Point& p2) {
		cv::line(image, p1, p2, line_color, 2, 4);
	}

	//Show image on screen
	void OpenCV::ShowImage(cv::Mat image) {
		cv::imshow("Demonstração", image);
	}

	//Save image in path
	void OpenCV::SaveImage(string path, Mat img) {
		cv::imwrite(path, img);
	}
}

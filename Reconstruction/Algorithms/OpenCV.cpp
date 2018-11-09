#include "stdafx.h"
#include "OpenCV.h"

namespace Algorithms {

	OpenCV::OpenCV()
	{
		line_color = Scalar(255.0, 255.0, 255.0);
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

	Mat OpenCV::Dilate(Mat img, int dilationSize)
	{
		Mat element = getStructuringElement(MORPH_ELLIPSE,
			Size(2 * dilationSize + 1, 2 * dilationSize + 1),
			Point(dilationSize, dilationSize));
		Mat result;
		dilate(img, result, element);
		return result;
	}
	Mat OpenCV::Erode(Mat img, int dilationSize)
	{
		Mat element = getStructuringElement(MORPH_ELLIPSE,
			Size(2 * dilationSize + 1, 2 * dilationSize + 1),
			Point(dilationSize, dilationSize));
		Mat result;
		erode(img, result, element);
		return result;
	}

	//Read a single image
	Mat OpenCV::ReadImage(string path)
	{
		Mat result;

		result = imread(path);

		if (!result.data)
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
	void OpenCV::ConnectedComponentsAlgorithm(Mat inputImage, vector<vector<Point>> &resultContours, vector<Vec4i> &hierarchy, int cvMode, int cvMethod)
	{
		findContours(inputImage, resultContours, hierarchy, cvMode, cvMethod);
	}

	//Draw the contours of an image
	void OpenCV::DrawContour(Mat &result, vector<vector<Point>> contours, int indice, Scalar color, int mode, int lineType, vector<Vec4i> hierarchy)
	{
		drawContours(result, contours, indice, color, mode, lineType, hierarchy);
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
	void OpenCV::ShowImage(cv::Mat image, string nameWindow) {
		imshow(nameWindow, image);
		waitKey();
	}

	//Save image in path
	void OpenCV::SaveImage(string path, Mat img) {
		cv::imwrite(path, img);
	}

	void OpenCV::NewWindow(string nameWindow)
	{
		namedWindow(nameWindow);
	}
	Mat OpenCV::Resize(Mat img, Size imgSize)
	{
		Mat temp;
		resize(img, temp, imgSize);

		return temp;
	}
}

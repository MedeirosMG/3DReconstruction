#ifndef ALGORITHMS_OPEN_CV
#define ALGORITHMS_OPEN_CV

#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\core\core.hpp"
#include <opencv2\calib3d\calib3d.hpp>
#include "opencv2\features2d.hpp"
#include "opencv2\nonfree\features2d.hpp"

using namespace cv;

namespace Algorithms {

	// Colocar todas as classes que serão usadas do OpenCV
	class OpenCV
	{
		private:
			cv::Scalar line_color;

		public:
			OpenCV();
			~OpenCV();
		
			Mat CannyAlgorithm(Mat img, double lowThresh, double highThresh, int kernelSize);		
			void ConnectedComponentsAlgorithm(Mat inputImage, vector<vector<Point>> &resultContours, vector<Vec4i> &hierarchy, int cvMode, int cvMethod);

			void DrawContour(Mat &result, vector<vector<Point>> contours, int indice, Scalar color, int mode, int lineType, vector<Vec4i> hierarchy);
			Mat ReadImage(string path);
			Mat ColorConverter(Mat image, int cvEnum);
			vector<KeyPoint> SiftDetector(cv::SiftFeatureDetector* detector, Mat img);
			Mat SiftDescriptor(Mat imgInput, vector<KeyPoint> keypoints);
			vector<DMatch> BFMatcher(Mat img1, Mat img2);
			void DrawLine(cv::Mat image, const cv::Point& p1, const cv::Point& p2);
			void ShowImage(cv::Mat image, string nameWindow);
			void SaveImage(string path, Mat img);
			void NewWindow(string nameWindow);
			Mat Resize(Mat img, Size imgSize);

			Mat Dilate(Mat img, int dilationSize);
			Mat Erode(Mat img, int dilationSize);

	};

}

#endif
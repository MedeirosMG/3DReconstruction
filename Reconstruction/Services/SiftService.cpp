#include "stdafx.h"
#include "SiftService.h"

namespace Services {

	SiftService::SiftService()
	{
		_openCv = new OpenCV();
	}
	
	SiftService::SiftService(OpenCV* openCv)
	{
		_openCv = openCv;
	}

	SiftService::~SiftService()
	{
	}

	//Detect fiducial points on the image
	SiftResult SiftService::Execute(Mat img1, Mat img2, int features, int layers, double contrast, double edge, double sigma)
	{
		//Sift Detector
		cv::SiftFeatureDetector detector(features, layers, contrast, edge, sigma);

		//Key points of images
		vector<KeyPoint> firstImgKeyPoints, secondImgKeyPoints;
		
		//Description of images
		Mat firstImgDescription, secondImgDescription;

		//Matches found in images
		vector<DMatch> matches;

		//-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
		std::vector< DMatch > good_matches;

		SiftResult result;
		//Number of lines and columns of the image
		float lin = img1.rows;
		float col = img1.cols;

		//Clear keypoints and matches vector
		firstImgKeyPoints.clear();
		secondImgKeyPoints.clear();
		matches.clear();

		//Finding images keypoints
		firstImgKeyPoints = _openCv->SiftDetector(&detector, img1);
		secondImgKeyPoints = _openCv->SiftDetector(&detector, img2);

		
		//Describing the images
		firstImgDescription = _openCv->SiftDescriptor(img1, firstImgKeyPoints);
		secondImgDescription = _openCv->SiftDescriptor(img2, secondImgKeyPoints);

		//Finding matches with Brute Force Matcher
		//matches = _openCv->BFMatcher(firstImgDescription, secondImgDescription);

		//Outro tipo de match
		FlannBasedMatcher matcher;
		matcher.match(firstImgDescription, secondImgDescription, matches);
		
	
		result.detector = detector;
		result.firstImgDescription = firstImgDescription;
		result.secondImgDescription = secondImgDescription;
		result.Matches = matches;
		result.FirstImageKeyPoints = firstImgKeyPoints;
		result.SecondImageKeyPoints = secondImgKeyPoints;
		
		drawMatches(img1, firstImgKeyPoints, img2, secondImgKeyPoints, matches, result.siftImg, Scalar::all(-1), Scalar::all(-1),
			vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
		return result;
	}

	SiftResult SiftService::Execute(Mat img1, Mat img2, Mat mask1, Mat mask2, int features, int layers, double contrast, double edge, double sigma)
	{
		//Sift Detector
		cv::SiftFeatureDetector detector(features, layers, contrast, edge, sigma);

		//Key points of images
		vector<KeyPoint> firstImgKeyPoints, secondImgKeyPoints;

		//Description of images
		Mat firstImgDescription, secondImgDescription;

		//Matches found in images
		vector<DMatch> matches;

		//-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
		std::vector< DMatch > good_matches;

		SiftResult result;
		//Number of lines and columns of the image
		float lin = img1.rows;
		float col = img1.cols;

		//Clear keypoints and matches vector
		firstImgKeyPoints.clear();
		secondImgKeyPoints.clear();
		matches.clear();

		//Finding images keypoints
		firstImgKeyPoints = _openCv->SiftDetector(&detector, img1);
		secondImgKeyPoints = _openCv->SiftDetector(&detector, img2);
		
		//Describing the images
		firstImgDescription = _openCv->SiftDescriptor(img1, firstImgKeyPoints);
		secondImgDescription = _openCv->SiftDescriptor(img2, secondImgKeyPoints);

		//Finding matches with Brute Force Matcher
		//matches = _openCv->BFMatcher(firstImgDescription, secondImgDescription);

		//Outro tipo de match
		FlannBasedMatcher matcher;
		matcher.match(firstImgDescription, secondImgDescription, matches);

		for (int i = 0; i < matches.size(); i++) {
			if (mask1.at<Vec3b>(firstImgKeyPoints[matches[i].queryIdx].pt.y, firstImgKeyPoints[matches[i].queryIdx].pt.x) != Vec3b(0, 0, 0)
				&& mask2.at<Vec3b>(secondImgKeyPoints[matches[i].trainIdx].pt.y, secondImgKeyPoints[matches[i].trainIdx].pt.x) != Vec3b(0, 0, 0)){
			// && result.Matches[i].distance < filterDist * min_dist) {
				result.Matches.push_back(matches[i]);
			}
		}

		result.detector = detector;
		result.firstImgDescription = firstImgDescription;
		result.secondImgDescription = secondImgDescription;
		result.FirstImageKeyPoints = firstImgKeyPoints;
		result.SecondImageKeyPoints = secondImgKeyPoints;

		drawMatches(mask1, firstImgKeyPoints, mask2, secondImgKeyPoints, result.Matches, result.siftImg, Scalar::all(-1), Scalar::all(-1),
			vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
		return result;
	}
}
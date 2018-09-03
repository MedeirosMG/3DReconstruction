#include "stdafx.h"
#include "RansacService.h"

namespace Services {

	RansacService::RansacService()
	{
		_openCv = new OpenCV();
	}

	RansacService::RansacService(OpenCV * openCv)
	{
		_openCv = openCv;
	}

	RansacService::~RansacService()
	{
	}

	Mat RansacService::FindRansacMask(SiftResult sift_result, double ransacThresh)
	{
		// Get all points
		vector<PointPair> points = Convert().DMatchToPointPair(sift_result.Matches, sift_result.FirstImageKeyPoints, sift_result.SecondImageKeyPoints);
		vector<Point2f> firstPoints;
		vector<Point2f> secondPoints;

		// Create point pair
		for each (PointPair item in points)
		{
			firstPoints.push_back(Convert().Point3fTo2f(item.FirstPoint));
			secondPoints.push_back(Convert().Point3fTo2f(item.SecondPoint));
		}

		// Find mask
		Mat mask;
		Mat H = findHomography(firstPoints, secondPoints, CV_RANSAC, 3.0, mask);
		
		return mask;
	}

	vector<PointPair> RansacService::Execute(SiftResult sift_result, double ransacThresh)
	{
		vector<PointPair> points = Convert().DMatchToPointPair(sift_result.Matches, sift_result.FirstImageKeyPoints, sift_result.SecondImageKeyPoints);
		Mat mask = FindRansacMask(sift_result, ransacThresh);
		
		vector< PointPair > ransacMatches;
		for (int i = 0; i < mask.rows; i++) {
			if ((unsigned int)mask.at<uchar>(i))
				ransacMatches.push_back(points[i]);
		}

		return ransacMatches;
	}

}
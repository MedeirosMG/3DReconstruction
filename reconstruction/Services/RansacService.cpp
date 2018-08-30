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

	vector<PointPair> RansacService::Execute(vector<PointPair> points, double ransacThresh)
	{
		vector<Point2f> leftPoints;
		vector<Point2f> rightPoints;
		for each (PointPair item in points)
		{
			Point2f first(item.FirstPoint.X, item.FirstPoint.Y);
			Point2f second(item.SecondPoint.X, item.SecondPoint.Y);

			leftPoints.push_back(first);
			rightPoints.push_back(second);
		}

		Mat mask;
		Mat H = findHomography(leftPoints, rightPoints, CV_RANSAC, 3.0, mask);
		vector< PointPair > ransacMatches;
		for (int i = 0; i < mask.rows; i++) {
			if ((unsigned int)mask.at<uchar>(i))
				ransacMatches.push_back(points[i]);
		}

		return ransacMatches;
	}

}
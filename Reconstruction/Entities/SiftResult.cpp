#include "stdafx.h"
#include "SiftResult.h"

namespace Entities {

	SiftResult::SiftResult()
	{
	}

	SiftResult::SiftResult(vector<DMatch> matches, vector<KeyPoint> firstImageKeyPoints, vector<KeyPoint> secondImageKeyPoints, SiftFeatureDetector detector, Mat firstDescriptor, Mat secondDescriptor) : Matches(matches), FirstImageKeyPoints(firstImageKeyPoints), SecondImageKeyPoints(secondImageKeyPoints), detector(detector), firstImgDescription(firstDescriptor), secondImgDescription(secondDescriptor){}

	SiftResult::~SiftResult()
	{
	}

}


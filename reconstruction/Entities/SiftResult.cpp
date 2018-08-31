#include "stdafx.h"
#include "SiftResult.h"

namespace Entities {

	SiftResult::SiftResult()
	{
	}

	SiftResult::SiftResult(vector<DMatch> matches, vector<KeyPoint> firstImageKeyPoints, vector<KeyPoint> secondImageKeyPoints) : Matches(matches), FirstImageKeyPoints(firstImageKeyPoints), SecondImageKeyPoints(secondImageKeyPoints) {}

	SiftResult::~SiftResult()
	{
	}

}


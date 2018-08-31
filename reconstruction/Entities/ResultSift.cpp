#include "stdafx.h"
#include "ResultSift.h"

namespace Entities {

	ResultSift::ResultSift()
	{
	}

	ResultSift::ResultSift(vector<DMatch> matches, vector<KeyPoint> firstImageKeyPoints, vector<KeyPoint> secondImageKeyPoints) : Matches(matches), FirstImageKeyPoints(firstImageKeyPoints), SecondImageKeyPoints(secondImageKeyPoints) {}

	ResultSift::~ResultSift()
	{
	}

}


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

	Mat CannyService::Execute(Mat inputImage, double lowThresh, double highThresh, int kernelSize)
	{
		Mat contour = _openCv->CannyAlgorithm(inputImage, lowThresh, highThresh, kernelSize);

		return contour;
	}

}
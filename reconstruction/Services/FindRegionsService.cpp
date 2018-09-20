#include "stdafx.h"
#include "FindRegionsService.h"

namespace Services {

	FindRegionsService::FindRegionsService()
	{
		_openCv = new OpenCV();
	}

	FindRegionsService::FindRegionsService(OpenCV * openCv)
	{
		_openCv = openCv;
	}


	FindRegionsService::~FindRegionsService()
	{
	}

	Mat FindRegionsService::Execute(Mat regions, string ImageToApply)
	{
		Mat imgOriginal = _openCv->ReadImage(ImageToApply);

		return Execute(regions, ImageToApply);
	}

	Mat FindRegionsService::Execute(Mat regions, Mat ImageToApply)
	{
		if (regions.rows != ImageToApply.rows || regions.cols != ImageToApply.cols)
			throw new exception("Imagens não tem o mesmo tamanho.");

		for (int y = 0; y < regions.rows; y++) {
			for (int x = 0; x < regions.cols; x++) {
				if (regions.at<Vec3b>(Point(x, y)) == Vec3b(0, 0, 0))
					ImageToApply.at<Vec3b>(Point(x, y)) = Vec3b(0, 0, 0);
			}
		}

		return ImageToApply;
	}

}
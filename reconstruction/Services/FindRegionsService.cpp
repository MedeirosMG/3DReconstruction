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

	vector<Mat> FindRegionsService::Execute(vector<Mat> regions, Mat ImageToApply)
	{
		vector<Mat> result;
		for (int i = 0; i < regions.size(); i++) {
			if (regions[i].rows != ImageToApply.rows || regions[i].cols != ImageToApply.cols)
				throw new exception("Imagens não tem o mesmo tamanho.");
			Mat img = ImageToApply.clone();
			for (int y = 0; y < regions[i].rows; y++) {
				for (int x = 0; x < regions[i].cols; x++) {
					if (regions[i].at<Vec3b>(Point(x, y)) == Vec3b(0, 0, 0))
						img.at<Vec3b>(Point(x, y)) = Vec3b(0, 0, 0);
				}
			}
			result.push_back(img);
		}
		return result;
	}

}
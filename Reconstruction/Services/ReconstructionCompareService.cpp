#include "stdafx.h"
#include "ReconstructionCompareService.h"

namespace Services {

	ReconstructionCompareService::ReconstructionCompareService()
	{
		_openCv = new OpenCV();
	}

	ReconstructionCompareService::ReconstructionCompareService(OpenCV * openCv)
	{
		_openCv = openCv;
	}


	ReconstructionCompareService::~ReconstructionCompareService()
	{
	}

	void ReconstructionCompareService::Execute(vector<Point3f> reconstructionPoints, string pathMap, string pathExport)
	{
		vector<ReconstructionComparison> result;
		PointUtilities *pointUtilities = new PointUtilities();
		Mat mapImage;
		ReadFilePFM(mapImage, pathMap);
		mapImage = mapImage / 255;
		resize(mapImage, mapImage, Size(REC_SCREEN_DEFAULT_WIDTH, REC_SCREEN_DEFAULT_HEIGHT));

		float maxPointReconstruction = pointUtilities->GetMaxAbsCoord(reconstructionPoints, "z");
		float maxPointMap = pointUtilities->GetMaxAbsCoord(mapImage, "z");
		
		for each (Point3f point in reconstructionPoints)
		{
			ReconstructionComparison reconstructionComparison;
			reconstructionComparison.Map.z = mapImage.at<float>((int)point.y, (int)point.x) / maxPointMap;
			reconstructionComparison.Reconstruction.z = point.z / maxPointReconstruction;
			reconstructionComparison.Error.z = abs(reconstructionComparison.Map.z - reconstructionComparison.Reconstruction.z);

			result.push_back(reconstructionComparison);
		}

		Export::Csv(result, pathExport, "z");
	}
}
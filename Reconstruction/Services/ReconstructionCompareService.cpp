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
		vector<ReconstructionComparison> resultNormalized;
		vector<ReconstructionComparison> result;
		PointUtilities *pointUtilities = new PointUtilities();
		Mat mapImage, mapImageResult;
		ReadFilePFM(mapImage, pathMap);
		mapImageResult = mapImage;
		resize(mapImageResult, mapImageResult, Size(REC_SCREEN_DEFAULT_WIDTH, REC_SCREEN_DEFAULT_HEIGHT));

		float maxPointReconstruction = pointUtilities->GetMaxAbsCoord(reconstructionPoints, "z");
		float minPointReconstruction = pointUtilities->GetMinAbsCoord(reconstructionPoints, "z");
		cout << "min calibration: " << minPointReconstruction << " max calibration:" << maxPointReconstruction << endl;
		float maxPointMap = pointUtilities->GetMaxAbsCoord(mapImageResult, "z");
		float minPointMap = pointUtilities->GetMinAbsCoord(mapImageResult, "z");
		cout << "min depth map: " << minPointMap << " max depth map:" << maxPointMap << endl;
		for each (Point3f point in reconstructionPoints)
		{
			ReconstructionComparison reconstructionComparison;
			ReconstructionComparison reconstructionComparison2;
			double Z = 171.548 *(6338 / (mapImageResult.at<float>((int)point.y, (int)point.x) + 479.489));
		
			//double Z = (mapImageResult.at<float>((int)point.y, (int)point.x));
			reconstructionComparison.Map.z = (Z - minPointMap) / (maxPointMap - minPointMap);
			if (reconstructionComparison.Map.z < 0)
				reconstructionComparison.Map.z = 0;
			//reconstructionComparison.Map.z = 1 - reconstructionComparison.Map.z;
			reconstructionComparison.Reconstruction.z = (point.z - minPointReconstruction) / (maxPointReconstruction - minPointReconstruction);
			reconstructionComparison.Error.z = sqrt(pow(reconstructionComparison.Map.z - reconstructionComparison.Reconstruction.z, 2));


			reconstructionComparison2.Map.z = Z;
			reconstructionComparison2.Reconstruction.z = point.z;
			resultNormalized.push_back(reconstructionComparison);
			result.push_back(reconstructionComparison2);
			
		}

		Export::Csv(resultNormalized, pathExport, "z");

		Export::Csv(result, pathExport + "_normal", "z");
	}
}
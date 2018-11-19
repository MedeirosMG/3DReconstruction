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

	void ReconstructionCompareService::Execute(vector<Point3f> reconstructionPoints, CameraProperties calib, string pathMap, string pathExport, std::map<string, double>* batchResult)
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

		float maxPointMap = pointUtilities->GetMaxAbsCoord(mapImageResult, "z", calib);
		float minPointMap = pointUtilities->GetMinAbsCoord(mapImageResult, "z", calib);
		cout << "min depth map: " << minPointMap << " max depth map:" << maxPointMap << endl;

		for each (Point3f point in reconstructionPoints)
		{
			ReconstructionComparison reconstructionComparisonNormalized;
			ReconstructionComparison reconstructionComparison;
			double Z = calib.B *(calib.f / (mapImageResult.at<float>((int)point.y, (int)point.x) + calib.doffs));

			float mapZ = (Z - minPointMap) / (maxPointMap - minPointMap);
			reconstructionComparisonNormalized.Map.z = mapZ < 0 ? 0 : mapZ;
			reconstructionComparisonNormalized.Reconstruction.z = (point.z - minPointReconstruction) / (maxPointReconstruction - minPointReconstruction);
			reconstructionComparisonNormalized.Error.z = sqrt(pow(reconstructionComparisonNormalized.Map.z - reconstructionComparisonNormalized.Reconstruction.z, 2));

			reconstructionComparison.Map.z = Z;
			reconstructionComparison.Reconstruction.z = point.z;

			resultNormalized.push_back(reconstructionComparisonNormalized);
			result.push_back(reconstructionComparison);
		}

		Export::Csv(resultNormalized, pathExport, "z");
		//Export::Csv(result, pathExport + "_normal", "z");

		// Add overall of all tests
		if (batchResult != NULL) {
			double average = 0.0;
			vector<string> splittedPath = StringHelper::Split(pathExport, '\\');
			int count = 0;

			for each (ReconstructionComparison item in resultNormalized)
			{
				if (!isinf(item.Error.z)) {
					average += item.Error.z;
					count++;
				}
			}

			average = average / count;
			batchResult->insert(pair<string, double>(splittedPath[splittedPath.size() - 1], average));
		}
	}
}
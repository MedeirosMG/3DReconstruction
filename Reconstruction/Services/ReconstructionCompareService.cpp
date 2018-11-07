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
		Mat mapImage;
		ReadFilePFM(mapImage, pathMap);
		mapImage = mapImage / 255;
		resize(mapImage, mapImage, Size(800, 600));

		PointUtilities *converter = new PointUtilities();

		vector<Point3f> pointsMap;
		for (int i = 0; i < mapImage.rows; i++)
		{
			for (int j = 0; i < mapImage.cols; j++)
			{
				float zPoint = mapImage.at<float>(i, j);
				pointsMap.push_back(Point3f(i, j, zPoint));
			}
		}

		float maxPointReconstruction = converter->GetMaxAbsCoord(reconstructionPoints, "z");
		float maxPointMap = converter->GetMaxAbsCoord(pointsMap, "z");

		
		for each (Point3f point in reconstructionPoints)
		{
			float zMap = mapImage.at<float>(point.x, point.y) / maxPointMap;
			float zReconstruction = point.z / maxPointReconstruction;

			float error = abs(zMap - zReconstruction);
		}

	}
}
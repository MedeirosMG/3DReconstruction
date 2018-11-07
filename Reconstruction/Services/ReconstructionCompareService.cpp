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

	void ReconstructionCompareService::Execute()
	{
		
	}
}
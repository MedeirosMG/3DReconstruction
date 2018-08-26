#include "stdafx.h"
#include "RansacService.h"

namespace Services {

	RansacService::RansacService()
	{
		_openCv = new OpenCV();
	}

	RansacService::RansacService(OpenCV * openCv)
	{
		_openCv = openCv;
	}

	RansacService::~RansacService()
	{
	}

}
#include "stdafx.h"
#include "RenderService.h"

namespace Services {
	RenderService::RenderService(OpenCV* openCv)
	{
		_openCv = openCv;
	}
	RenderService::RenderService()
	{
		_openCv = new OpenCV();
	}


	RenderService::~RenderService()
	{
	}

}
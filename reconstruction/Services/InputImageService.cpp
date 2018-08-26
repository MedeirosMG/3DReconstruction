#include "stdafx.h"
#include "InputImageService.h"

namespace Services {

	InputImageService::InputImageService()
	{
		_openCv = new OpenCV();
	}
	
	InputImageService::InputImageService(OpenCV* openCv)
	{
		_openCv = openCv;
	}

	InputImageService::~InputImageService()
	{
	}

	//Detect fiducial points on the image
	Mat InputImageService::Execute(string path) {
		return _openCv->ReadImage(path);
	}
}
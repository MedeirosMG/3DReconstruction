#include "stdafx.h"
#include "PointsUtilities.h"

namespace Utilities {
	CustomPoint::CustomPoint()
	{
		_openCv = new OpenCV();
	}

	CustomPoint::CustomPoint(OpenCV* openCv)
	{
		_openCv = openCv;
	}


	CustomPoint::~CustomPoint()
	{
	}
}
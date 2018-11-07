#include "stdafx.h"
#include "CameraProperties.h"

namespace Entities {	

	CameraProperties::CameraProperties(float b, float lambda, float cameraDistance) 
		: B(b), Lambda(lambda), CameraDistance(cameraDistance)
	{
	}

	CameraProperties::CameraProperties()
	{
	}

	CameraProperties::~CameraProperties()
	{
	}

}


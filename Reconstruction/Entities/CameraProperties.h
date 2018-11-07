#ifndef ENTITIES_CAMERA_PROPERTIES
#define ENTITIES_CAMERA_PROPERTIES

namespace Entities {

	class CameraProperties {
		public:
			CameraProperties(float b, float lambda, float cameraDistance);
			CameraProperties();
			~CameraProperties();

			float B;
			float Lambda;
	};

}

#endif
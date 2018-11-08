#ifndef ENTITIES_CAMERA_PROPERTIES
#define ENTITIES_CAMERA_PROPERTIES

namespace Entities {

	class CameraProperties {
		public:
			CameraProperties(float b, float lambda);
			CameraProperties();
			~CameraProperties();

			float B = 1;
			float Lambda = 1;
	};

}

#endif
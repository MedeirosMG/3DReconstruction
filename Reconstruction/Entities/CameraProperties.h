#ifndef ENTITIES_CAMERA_PROPERTIES
#define ENTITIES_CAMERA_PROPERTIES

namespace Entities {

	class CameraProperties {
		public:
			CameraProperties(float b, float lambda);
			CameraProperties();
			~CameraProperties();

			float f = 1;
			float width = 1;
			float B = 1;
			float Lambda = 1;
			float doffs = 1;
			float K = 1;
	};

}

#endif
#ifndef ENTITIES_RENDER_PROPERTIES
#define ENTITIES_RENDER_PROPERTIES

#include "../Algorithms/OpenCV.h"

namespace Entities {

	class RenderProperties {
		public:
			RenderProperties(float rotationDegree);
			~RenderProperties();

			// Rotation properties
			float _RotationDegree;
			int _rotateX = 0;
			int _rotateY = 0;
			bool _rotate = false;

			// TypeDraw properties
			int _typeImage = 0;

			//Triangles
			vector<Vec<Point3f, 3>> _triangles;
	};

}

#endif
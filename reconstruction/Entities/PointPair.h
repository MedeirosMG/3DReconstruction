#ifndef ENTITIES_POINT_PAIR
#define ENTITIES_POINT_PAIR

#include "CustomPoint.h"

namespace Entities {

	class PointPair {
		public:
			CustomPoint FirstPoint;
			CustomPoint SecondPoint;
			PointPair(CustomPoint firstPoint, CustomPoint secondPoint);
			~PointPair();
	};

}

#endif
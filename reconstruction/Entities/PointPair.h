#ifndef ENTITIES_POINT_PAIR
#define ENTITIES_POINT_PAIR

#include "../Algorithms/OpenCV.h"

namespace Entities {

	class PointPair {
		public:
			Point3f FirstPoint;
			Point3f SecondPoint;
			PointPair(Point3f firstPoint, Point3f secondPoint);
			~PointPair();
	};

}

#endif
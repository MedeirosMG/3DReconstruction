#ifndef ENTITIES_CUSTOM_POINT
#define ENTITIES_CUSTOM_POINT

#include "../Algorithms/OpenCV.h"

namespace Entities {
	class CustomPoint
	{
		public:
			~CustomPoint();
			float X;
			float Y;
			float Z;
			CustomPoint(float x, float y, float z);
			CustomPoint();
			Point3f ReturnPoint3f();
			vector<Point3f> ReturnPoint3f(vector<CustomPoint> points);
	};
}

#endif
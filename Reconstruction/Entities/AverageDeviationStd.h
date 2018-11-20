#ifndef ENTITIES_AVERAGE_DEVIATION_STD
#define ENTITIES_AVERAGE_DEVIATION_STD
#include "../Algorithms/OpenCV.h"

namespace Entities {

	class AverageDeviationStd {
		public:
			AverageDeviationStd();
			~AverageDeviationStd();

			double Average;
			double Deviation;
	};

}

#endif
#ifndef ENTITIES_RECONSTRUCTION_COMPARISON
#define ENTITIES_RECONSTRUCTION_COMPARISON
#include "../Algorithms/OpenCV.h"

namespace Entities {

	class ReconstructionComparison {
		public:
			ReconstructionComparison();
			~ReconstructionComparison();

			Point3f Map;
			Point3f Reconstruction;
			Point3f Error;
	};

}

#endif
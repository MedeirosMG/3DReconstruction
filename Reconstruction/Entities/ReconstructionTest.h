#ifndef ENTITIES_RECONSTRUCTION_TEST
#define ENTITIES_RECONSTRUCTION_TEST
#include "../Algorithms/OpenCV.h"

namespace Entities {

	class ReconstructionTest {
		public:
			ReconstructionTest();
			~ReconstructionTest();

			// Path of structured images
			string PathFirstStructuredImage;
			string PathSecondStructuredImage;

			// Path of unstructured images
			string PathFirstUnstructuredImage;
			string PathSecondUnstructuredImage;
						
			// Path of camera properties
			string PathCalib; 

			// Path of disparity file
			string PathDisparity;

			// Path of export file to compare reconstructions
			string PathExportComparison;
	};

}

#endif
#ifndef AUTOMATED_TEST_BATCH_RECONSTRUCTION
#define AUTOMATED_TEST_BATCH_RECONSTRUCTION
#include <iostream>
#include "..\Services\ControllerService.h"
#include "..\Helpers\Time.h"
#include "..\Helpers\Console.h"
#include "..\Helpers\Export.h"
#include "..\Helpers\Import.h"
#include "..\Entities\ReconstructionTest.h"

using namespace std;
using namespace Helpers;
using namespace Entities;
using namespace Services;

namespace AutomatedTests {

	class BatchReconstruction
	{
		private:
			Time* _time;
			vector<ReconstructionTest> ListReconstructions;
			void Add(string pathFirstStructuredImage, string pathSecondStructuredImage, string pathFirstUnstructuredImage, 
				string pathSecondUnstructuredImage, string pathCalib, string pathDisparity, string pathExportComparison);
			
			// Load Properties Methods for each test method
			void LoadPropertiesExample();

		public:
			BatchReconstruction();
			~BatchReconstruction();

			// Test methods
			void Example();
	};

}

#endif
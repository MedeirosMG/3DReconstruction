#ifndef HELPERS_EXPORT_VTK
#define HELPERS_EXPORT_VTK
#include <iostream>
#include <fstream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"
#include "../Entities/ReconstructionComparison.h"
#include "../Helpers/Time.h"
#include "../Helpers/StringHelper.h"
#include "../Entities/AverageDeviationStd.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;

namespace Helpers {

	class ExportVtk : vtkOBJExporter
	{
		public:
			ExportVtk();
			~ExportVtk();

			bool ExportObj(vtkActor *a, string path_export);
	};

}

#endif
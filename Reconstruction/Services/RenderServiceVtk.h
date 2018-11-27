#ifndef ALGORITHMS_RENDER_VTK
#define ALGORITHMS_RENDER_VTK
#include <iostream>

#include "../Helpers/PointsUtilities.h"
#include "../Entities/RenderProperties.h"
#include "../Helpers/Convert.h"
#include "../Helpers/Export.h"
#include "../Services/DelaunayService.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;
using namespace Helpers;

namespace Services {
	class RenderServiceVtk
	{
		private:
			void Init();

		public:
			void Execute(vector<Vec<Point3f, 4>> triangles, vector<Point3f> pointsCalibration, vector<Point3f> contour, string pathDirectoryExport = "", string filenameExport= "");
	};

}

#endif

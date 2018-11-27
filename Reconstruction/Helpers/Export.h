#ifndef HELPERS_EXPORT
#define HELPERS_EXPORT
#include <iostream>
#include <fstream>

#include <vtkOBJExporter.h>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"
#include "../Entities/ReconstructionComparison.h"
#include "../Helpers/Time.h"
#include "../Helpers/ExportVtk.h"
#include "../Helpers/StringHelper.h"
#include "../Entities/AverageDeviationStd.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;

namespace Helpers {
	// Circular including
	class Time;	

	class Export
	{
		private:
			static inline string Splitter = ";";

		public:
			Export();
			~Export();

			static bool Json(vector<Point3f> listPoints, string pathDirectory);
			static bool Obj(vector<Point3f> listPoints, string pathDirectory);
			static bool Obj(vtkActor *vtkActor, string pathDirectory);
			static bool Csv(Time time, string pathDirectory);
			static bool Csv(vector<ReconstructionComparison> reconstructionComparison, string pathDirectory, string coordinates = "xyz");
			static bool Csv(map<string, double> result, string pathDirectory);
			static bool Csv(map<string, AverageDeviationStd*> result, string pathDirectory);
	};

}

#endif
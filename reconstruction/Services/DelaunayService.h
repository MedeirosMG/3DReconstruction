#ifndef SERVICES_DELAUNAY
#define SERVICES_DELAUNAY
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"
#include "../Helpers/PointsUtilities.h"
#include "../Helpers/Convert.h"
#include "../Helpers/ReconstructionDefine.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;
using namespace Helpers;

namespace Services {

	// Implementar funções do Delaunay utilizando os Algorithms
	class DelaunayService
	{
		private:
			OpenCV* _openCv;
			vector<Vec6f> FilterTriangles(vector<Vec6f> triangles, Mat contour, Size screenSize);
			bool CheckInsidePoint(Point2f points, Mat contour);

		public:
			DelaunayService(OpenCV* openCv);
			DelaunayService();
			~DelaunayService();
			vector<Vec6f> Execute(vector<Point3f> pointsCalibration, vector<Point3f> contour, Mat contourDilated, Size sizeImg = Size(1,1));
			void TestExecute(vector<Point3f> points = vector<Point3f>());
			vector<Vec6f> RemoveRectangle(vector<Vec6f> triangles);
			bool CheckRectangle(int coord, Vec6f triangle);
	};

}

#endif
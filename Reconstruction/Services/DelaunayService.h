#ifndef SERVICES_DELAUNAY
#define SERVICES_DELAUNAY
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"
#include "../Helpers/PointsUtilities.h"
#include "../Helpers/Convert.h"
#include "../Helpers/ReconstructionDefine.h"
#include <vtkCellArray.h>
#include <vtkDelaunay3D.h>
#include <vtkMinimalStandardRandomSequence.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkProperty.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolygon.h>
#include <vtkSmartPointer.h>
#include <vtkMath.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkClipClosedSurface.h>
#include <vtkCleanPolyData.h>
#include <vtkDelaunay3D.h>
#include <vtkDelaunay2D.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkSurfaceReconstructionFilter.h>
#include <vtkContourFilter.h>
#include <vtkPlane.h>
#include <vtkPlaneCollection.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkReverseSense.h>
#include <vtkTriangle.h>

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
			vector<Vec<Point3f, 4>> FilterTriangles(vector<Vec<Point3f, 4>> triangles, Mat contour, Size screenSize);
			bool CheckInsidePoint(Point2f points, Mat contour);

		public:
			DelaunayService(OpenCV* openCv);
			DelaunayService();
			~DelaunayService();
			vector<Vec<Point3f, 4>> Execute(vector<Point3f> pointsCalibration, vector<Point3f> contour, Mat contourDilated, Size sizeImg = Size(1,1));
			void TestExecute(vector<Point3f> points = vector<Point3f>());
			vector<Vec6f> RemoveRectangle(vector<Vec6f> triangles);
			bool CheckRectangle(int coord, Vec6f triangle);
			vector<Vec<Point3f, 4>> GetTriangles(vtkUnstructuredGrid *unstructuredGrid);
	};

}

#endif
#ifndef HELPERS_POINT_UTILITIES
#define HELPERS_POINT_UTILITIES
#include <iostream>
#include <fstream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"
#include "../Entities/SiftResult.h"
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

namespace Helpers {

	class PointUtilities
	{
		private:
			OpenCV * _openCv;

		public:
			PointUtilities(OpenCV* openCv);
			PointUtilities();
			~PointUtilities();

			vector<Point3f> PointsTranslocate(vector<Point3f> points, float maxValue);
			vector<Vec6f> PointsTranslocate(vector<Vec6f> points, float maxValue);
			vector<Point3f> PointsZoom(vector<Point3f> points, int zoom);
			float GetMaxAbsCoord(vector<Point3f> points, string coordinate);
			float GetMaxAbsCoord(vector<Vec6f> points);
			float GetMaxAbsCoord(vector<Vec<Point3f, 3>> points);
			vector<Point3f> GetMockPoints(string fileRead = ".\\Others Files\\MockPoints.obj");
			Point2f GetMiddlePoint(Point2f pt1, Point2f pt2);
			vector<Point3f> MergePoints(vector<Point3f> pts1, vector<Point3f> pts2);
			vector<PointPair> MergePoints(vector<PointPair> pts1, vector<PointPair> pts2);
			vector<Point3f> PixelToCoordenate(vector<Point3f> points, Size screenSize);
			Point3f PixelToCoordenate(Point3f point, Size screenSize);
			Point3f CoordenateToPixel(Point3f point, Size screenSize);
			vector<PointPair> PixelToCoordenate(vector<PointPair> points, Size screenSize);
			SiftResult FilterKeyPoints(SiftResult result, int filterY, int filterDist, Mat img1, Mat img2);
			double GetArea(vector<Point> points);
			void FillUnstructuredGrid(vtkUnstructuredGrid * unstructuredGrid, vector<Point3f> pointsToApply);
			void FillUnstructuredGrid2(vtkUnstructuredGrid * unstructuredGrid, vector<Vec< Point3f, 4> > triangles);
			bool CheckInsidePoint(Point2f point, Mat contour);
	};

}

#endif
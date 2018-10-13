
#define vtkRenderingCore_AUTOINIT 2(vtkRenderingOpenGL2, vtkInteractionStyle)
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
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void InitializeUnstructuredGrid(vtkUnstructuredGrid *unstructuredGrid, string filename)
{
	vtkSmartPointer<vtkMinimalStandardRandomSequence> randomSequence
		= vtkSmartPointer<vtkMinimalStandardRandomSequence>::New();
	randomSequence->SetSeed(4);

	ifstream file(filename, std::ios::in);
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();

	vector < vector<double> > p;

	points->SetDataType(VTK_DOUBLE);
	double point[3];
	while (file >> point[0] >> point[1] >> point[2]) {
		vector<double> t;
		t.push_back(point[0]);
		t.push_back(point[1]);
		t.push_back(point[2]);
		p.push_back(t);
	}
	int n = p.size();
	cells->InsertNextCell(n);
	for (int i = 0; i < n; i++) {
		point[0] = p[i][0];
		point[1] = p[i][1];
		if (p[i][2] >= 0)
			point[2] = p[i][2];
		else
			point[2] = 0;
		cells->InsertCellPoint(points->InsertNextPoint(point));
	}



	points->Squeeze();
	unstructuredGrid->SetPoints(points);
	cells->Squeeze();
	unstructuredGrid->SetCells(VTK_VERTEX, cells);
}
void exportUnstructuredGrid(vtkUnstructuredGrid *unstructuredGrid, string filename) {


	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	points = unstructuredGrid->GetPoints();
	vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
	cells = unstructuredGrid->GetCells();
	vtkSmartPointer<vtkPolyData> polydata =
		vtkSmartPointer<vtkPolyData>::New();
	std::ofstream outFile("triangles.txt");
	//add the geometry and topology to the polydata
	polydata->SetPoints(points);
	polydata->SetPolys(cells);
	for (vtkIdType i = 0; i < unstructuredGrid->GetNumberOfCells(); i++)
	{
		vtkCell* cell = unstructuredGrid->GetCell(i);
		double p0[3];
		double p1[3];
		double p2[3];

		cell->GetPoints()->GetPoint(0, p0);
		//std::cout << "p0: " << p0[0] << " " << p0[1] << " " << p0[2] << std::endl;
		cell->GetPoints()->GetPoint(1, p1);
		//std::cout << "p1: " << p1[0] << " " << p1[1] << " " << p1[2] << std::endl;
		cell->GetPoints()->GetPoint(2, p2);
		//std::cout << "p2: " << p2[0] << " " << p2[1] << " " << p2[2] << std::endl;

		// the important part
		outFile << p0[0] << " " << p0[1] << " " << p0[2] << "\n";

		outFile << p1[0] << " " << p1[1] << " " << p1[2] << "\n";

		outFile << p2[0] << " " << p2[1] << " " << p2[2] << "\n";
	}
	/*double p[3];
	for (vtkIdType i = 0; i < points->GetNumberOfPoints(); i++) {
	points->GetPoint(i, p);

	cout << p[0] << " " << p[1] << " " << p[2] << endl;
	}*/

}

int Delaunay3D(int dataType, int outputPointsPrecision)
{
	vtkSmartPointer<vtkUnstructuredGrid> inputUnstructuredGrid
		= vtkSmartPointer<vtkUnstructuredGrid>::New();
	InitializeUnstructuredGrid(inputUnstructuredGrid, "points.txt");

	vtkSmartPointer<vtkDelaunay3D> delaunay
		= vtkSmartPointer<vtkDelaunay3D>::New();
	delaunay->SetOutputPointsPrecision(outputPointsPrecision);
	delaunay->SetInputData(inputUnstructuredGrid);

	delaunay->Update();

	vtkSmartPointer<vtkUnstructuredGrid> outputUnstructuredGrid = delaunay->GetOutput();
	vtkSmartPointer<vtkPoints> points = outputUnstructuredGrid->GetPoints();

	return points->GetDataType();
}


int main() {

	//le os pontos
	vtkSmartPointer<vtkUnstructuredGrid> inputUnstructuredGrid
		= vtkSmartPointer<vtkUnstructuredGrid>::New();
	InitializeUnstructuredGrid(inputUnstructuredGrid, "points.txt");
	vtkSmartPointer<vtkDataSetMapper> originalMapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	originalMapper->SetInputData(inputUnstructuredGrid);

	//Ator para renderizar os pontos
	vtkSmartPointer<vtkActor> originalActor =
		vtkSmartPointer<vtkActor>::New();
	originalActor->SetMapper(originalMapper);
	originalActor->GetProperty()->SetColor(1, 1, 1);

	//Delaunay 3D
	vtkSmartPointer<vtkDelaunay3D> delaunay3D =
		vtkSmartPointer<vtkDelaunay3D>::New();
	//delaunay3D->SetInputData(inputUnstructuredGrid);
	//entrada do delaunay
	delaunay3D->SetInputData(inputUnstructuredGrid);
	/*
	vtkSmartPointer<vtkDataSetSurfaceFilter> surfaceFilter =
	vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
	surfaceFilter->SetInputConnection(delaunay3D->GetOutputPort());
	surfaceFilter->Update()*/
	vtkSmartPointer<vtkDataSetMapper> delaunayMapper =
		vtkSmartPointer<vtkDataSetMapper>::New();

	delaunayMapper->SetInputConnection(delaunay3D->GetOutputPort());
	vtkSmartPointer<vtkUnstructuredGrid> outputUnstructuredGrid
		= vtkSmartPointer<vtkUnstructuredGrid>::New();
	outputUnstructuredGrid = delaunay3D->GetOutput();
	//Ator do delaunay para renderizar
	vtkSmartPointer<vtkActor> delaunayActor =
		vtkSmartPointer<vtkActor>::New();
	delaunayActor->SetMapper(delaunayMapper);
	delaunayActor->GetProperty()->SetColor(1, 1, 1);
	delaunayActor->GetProperty()->SetRepresentationToWireframe();

	exportUnstructuredGrid(outputUnstructuredGrid, "triangles.txt");

	// Visualize

	// Define viewport ranges
	// (xmin, ymin, xmax, ymax)
	double leftViewport[4] = { 0.0, 0.0, 0.5, 1.0 };
	double rightViewport[4] = { 0.5, 0.0, 1.0, 1.0 };

	// Create a renderer, render window, and interactor
	vtkSmartPointer<vtkRenderer> originalRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderer> delaunayRenderer =
		vtkSmartPointer<vtkRenderer>::New();

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->SetSize(1500, 800);

	renderWindow->AddRenderer(originalRenderer);
	originalRenderer->SetViewport(leftViewport);
	renderWindow->AddRenderer(delaunayRenderer);
	delaunayRenderer->SetViewport(rightViewport);

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	originalRenderer->AddActor(originalActor);
	delaunayRenderer->AddActor(delaunayActor);
	originalRenderer->SetBackground(.0, .0, .0);
	delaunayRenderer->SetBackground(.0, .0, .0);

	// Render and interact
	renderWindow->Render();
	renderWindowInteractor->Start();
	return EXIT_SUCCESS;
}
#include "stdafx.h"

#include "RenderService.h"
#include "RenderServiceVtk.h"
#include <vtkAutoInit.h> 

namespace Services {
	void RenderServiceVtk::Execute(vector<Vec<Point3f, 4>> triangles, vector<Point3f> pointsCalibration, vector<Point3f> contour)
	{

		VTK_MODULE_INIT(vtkRenderingOpenGL2)
		VTK_MODULE_INIT(vtkInteractionStyle)

		PointUtilities *utilitie = new PointUtilities();

		// Size of screen to render
		double leftViewport[4] = { 0.0, 0.0, 0.5, 1.0 };
		double rightViewport[4] = { 0.5, 0.0, 1.0, 1.0 };

		// Multiple renders
		vtkSmartPointer<vtkRenderer> originalRenderer = vtkSmartPointer<vtkRenderer>::New();
		vtkSmartPointer<vtkRenderer> delaunayRenderer = vtkSmartPointer<vtkRenderer>::New();

		vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
		renderWindow->SetSize(1500, 800);
		
		// First render
		renderWindow->AddRenderer(originalRenderer);
		originalRenderer->SetViewport(leftViewport);

		// Second render
		renderWindow->AddRenderer(delaunayRenderer);
		delaunayRenderer->SetViewport(rightViewport);

		

		// For points apply
		vtkSmartPointer<vtkUnstructuredGrid> inputUnstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
		//utilitie->FillUnstructuredGrid(inputUnstructuredGrid, utilitie->MergePoints(contour, pointsCalibration));
		utilitie->FillUnstructuredGrid(inputUnstructuredGrid, pointsCalibration);
		vtkSmartPointer<vtkDataSetMapper> originalMapper = vtkSmartPointer<vtkDataSetMapper>::New();
		originalMapper->SetInputData(inputUnstructuredGrid);

		vtkSmartPointer<vtkActor> originalActor = vtkSmartPointer<vtkActor>::New();
		originalActor->SetMapper(originalMapper);
		originalActor->GetProperty()->SetColor(1, 1, 1);
		originalActor->GetProperty()->SetPointSize(3.0);
		vtkSmartPointer<vtkUnstructuredGrid> delaunayUnstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
		utilitie->FillUnstructuredGrid2(delaunayUnstructuredGrid, triangles);
		vtkSmartPointer<vtkDataSetMapper> delaunayMapper = vtkSmartPointer<vtkDataSetMapper>::New();
		delaunayMapper->SetInputData(delaunayUnstructuredGrid);

		vtkSmartPointer<vtkActor> delaunayActor = vtkSmartPointer<vtkActor>::New();
		delaunayActor->SetMapper(delaunayMapper);
		delaunayActor->GetProperty()->SetColor(1, 1, 1);

		//Wireframe
		//delaunayActor->GetProperty()->SetRepresentationToWireframe();




		// Add interact
		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
		renderWindowInteractor->SetRenderWindow(renderWindow);

		originalRenderer->AddActor(originalActor);
		delaunayRenderer->AddActor(delaunayActor);
		originalRenderer->SetBackground(.0, .0, .0);
		delaunayRenderer->SetBackground(.0, .0, .0);

		renderWindow->Render();
		renderWindowInteractor->Start();
	}
}
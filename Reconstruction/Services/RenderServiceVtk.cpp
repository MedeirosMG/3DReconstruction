#include "stdafx.h"
#include "RenderService.h"
#include "RenderServiceVtk.h"

namespace Services {
	void RenderServiceVtk::Execute(vector<Vec<Point3f, 3>> triangles, vector<Point3f> pointsCalibration, vector<Point3f> contour)
	{
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

		// Add interact
		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
		renderWindowInteractor->SetRenderWindow(renderWindow);

		// For points apply
		vtkSmartPointer<vtkUnstructuredGrid> inputUnstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
		utilitie->FillUnstructuredGrid(inputUnstructuredGrid, utilitie->MergePoints(contour, pointsCalibration));
		vtkSmartPointer<vtkDataSetMapper> originalMapper = vtkSmartPointer<vtkDataSetMapper>::New();
		originalMapper->SetInputData(inputUnstructuredGrid);

		vtkSmartPointer<vtkActor> originalActor = vtkSmartPointer<vtkActor>::New();
		originalActor->SetMapper(originalMapper);
		originalActor->GetProperty()->SetColor(1, 1, 1);

		originalRenderer->AddActor(originalActor);
		//delaunayRenderer->AddActor(delaunayActor);
		originalRenderer->SetBackground(.0, .0, .0);
		delaunayRenderer->SetBackground(.0, .0, .0);

		renderWindow->Render();
		renderWindowInteractor->Start();
	}
}
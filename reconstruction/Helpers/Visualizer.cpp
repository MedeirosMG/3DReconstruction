#include "stdafx.h"
#include "Visualizer.h"

namespace Helpers {

	Visualizer::Visualizer(string WindowName, OpenCV * opencv)
	{
		_openCv = opencv;

		if (WindowName != "")
			namedWindow(WindowName);
	}

	Visualizer::Visualizer(OpenCV * opencv)
	{
		_openCv = opencv;
	}

	Visualizer::~Visualizer() {}

	void Visualizer::NewWindow(string WindowName)
	{
		_openCv->NewWindow(WindowName);
	}

	void Visualizer::Show(Mat Img, string WindowName)
	{
		if (WindowName == "")
			return;

		cout << "---- Showing image, press any key to continue ----" << endl;
		_openCv->ShowImage(Img, WindowName);
	}

	void Visualizer::Show(vector<Point3f> points)
	{
		Console().Print(points);
	}

	void Visualizer::Show(vector<Vec6f> triangles)
	{
		Console().Print(triangles);
	}

	void Visualizer::Show(SiftResult result)
	{
		Console().Print(result);
	}

	void Visualizer::Show(vector<PointPair> points)
	{
		Console().Print(points);
	}
}
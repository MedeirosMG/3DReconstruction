#include "stdafx.h"
#include "Visualizer.h"

namespace Helpers {

	Visualizer::Visualizer(string WindowName, OpenCV * opencv, bool execute)
	{
		_openCv = opencv;
		_execute = execute;

		if (WindowName != "" && execute)
			namedWindow(WindowName);
	}

	Visualizer::Visualizer(OpenCV * opencv)
	{
		_openCv = opencv;
	}

	Visualizer::~Visualizer() {}

	void Visualizer::SetExecute(bool execute)
	{
		_execute = execute;
	}

	void Visualizer::NewWindow(string WindowName)
	{
		_openCv->NewWindow(WindowName);
	}

	void Visualizer::Show(Mat Img, string WindowName)
	{
		if (!_execute)
			return;

		cout << "---- Showing image, press any key to continue ----" << endl;
		_openCv->ShowImage(Img, WindowName);
	}

	void Visualizer::Show(vector<Point3f> points)
	{
		if (!_execute)
			return;

		Console().Print(points);
	}

	void Visualizer::Show(vector<Vec6f> triangles)
	{
		if (!_execute)
			return;

		Console().Print(triangles);
	}

	void Visualizer::Show(SiftResult result, string WindowName)
	{
		if (!_execute)
			return;
		cout << "---- Showing image, press any key to continue ----" << endl;
		_openCv->ShowImage(result.siftImg, WindowName);
		Console().Print(result);
	}

	void Visualizer::Show(vector<PointPair> points)
	{
		if (!_execute)
			return;

		Console().Print(points);
	}
}
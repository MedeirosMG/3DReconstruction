#ifndef HELPERS_VISUALIZER
#define HELPERS_VISUALIZER
#include <iostream>
#include <fstream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Entities/PointPair.h"
#include "../Helpers/Console.h"

using namespace std;
using namespace Algorithms;
using namespace Entities;

namespace Helpers {

	class Visualizer
	{
		private:
			OpenCV * _openCv;
			bool _execute;

		public:
			Visualizer(string WindowName, OpenCV* opencv = new OpenCV());
			Visualizer(OpenCV* opencv = new OpenCV());
			~Visualizer();

			void SetExecute(bool execute);
			void NewWindow(string WindowName);
			void Show(Mat Img, string WindowName);
			void Show(vector<Point3f> points);
			void Show(vector<PointPair> points);
			void Show(vector<Vec6f> triangles);
			void Show(SiftResult result);
	};
}

#endif
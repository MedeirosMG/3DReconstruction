#include "stdafx.h"
#include "RenderService.h"

namespace Services {

	vector<Vec6f> RenderService::_triangles;
	vector<Point3f> RenderService::_points3D;

	RenderService::RenderService(OpenCV* openCv)
	{
		_openCv = openCv;
	}
	RenderService::RenderService()
	{
		_openCv = new OpenCV();
	}


	RenderService::~RenderService()
	{
	}

	void draw(void) {
		
		glColor3f(0.1, 0.2, 0.3);
		RenderService *service = new RenderService();
		PointUtilities *converter = new PointUtilities();

		// Get triangles and points setted
		vector<Vec6f> triangleList = service->GetTriangles();
		vector<Point3f> points = service->GetPoints();
		
		float maxAbs = converter->GetMaxAbsCoord(triangleList);

		
		// Draw triangles
		for (size_t i = 3; i < triangleList.size(); i++) {
			Vec6f triangle = triangleList[i];
			Point pt1{ cvRound(triangle[0]), cvRound(triangle[1]) };
			Point pt2{ cvRound(triangle[2]), cvRound(triangle[3]) };
			Point pt3{ cvRound(triangle[4]), cvRound(triangle[5]) };
			
			/*
			glBegin(GL_LINES);
				glVertex3f(pt1.x/maxAbs, pt1.y/maxAbs, 0);
				glVertex3f(pt2.x/maxAbs, pt2.y/maxAbs, 0);
			glEnd();

			glBegin(GL_LINES);
				glVertex3f(pt2.x / maxAbs, pt2.y / maxAbs, 0);
				glVertex3f(pt3.x / maxAbs, pt3.y / maxAbs, 0);
			glEnd();

			glBegin(GL_LINES);
				glVertex3f(pt3.x / maxAbs, pt3.y / maxAbs, 0);
				glVertex3f(pt1.x / maxAbs, pt1.y / maxAbs, 0);
			glEnd();*/
		}

		Mat image = imread(".\\Others Files\\cabeca_1.png", CV_8UC3);
		vector<Vec4i> hierarchy;
		vector<vector<Point> > contours;
		findContours(image, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

		Mat raw_dist(image.size(), CV_32FC1);
		for (int j = 0; j < image.rows; j++)
		{
			for (int i = 0; i < image.cols; i++)
			{
				raw_dist.at<float>(j, i) = (float)pointPolygonTest(contours[0], Point2f((float)i, (float)j), true);
			}
		}

		double minVal; double maxVal;
		minMaxLoc(raw_dist, &minVal, &maxVal, 0, 0, Mat());
		minVal = abs(minVal); maxVal = abs(maxVal);
		Mat drawing = Mat::zeros(image.size(), CV_8UC3);
		for (int j = 0; j < image.rows; j++)
		{
			for (int i = 0; i < image.cols; i++)
			{
				if (raw_dist.at<float>(j, i) < 0)
				{
					drawing.at<Vec3b>(j, i)[0] = (uchar)(255 - abs(raw_dist.at<float>(j, i)) * 255 / minVal);
				}
				else if (raw_dist.at<float>(j, i) > 0)
				{
					drawing.at<Vec3b>(j, i)[2] = (uchar)(255 - raw_dist.at<float>(j, i) * 255 / maxVal);
				}
				else
				{
					drawing.at<Vec3b>(j, i)[0] = 255; drawing.at<Vec3b>(j, i)[1] = 255; drawing.at<Vec3b>(j, i)[2] = 255;
				}
			}
		}
		const char* source_window = "Source";
		namedWindow(source_window, WINDOW_AUTOSIZE);
		imshow(source_window, image);
		namedWindow("Distance", WINDOW_AUTOSIZE);
		imshow("Distance", drawing);

		glFlush();
	}

	vector<Vec6f> RenderService::GetTriangles() 
	{
		return _triangles;
	}
	vector<Point3f> RenderService::GetPoints()
	{ 
		return _points3D;
	}

	void RenderService::Init(int width, int height, vector<Vec6f> triangles, vector<Point3f> points3D)
	{
		//Set the objects for render
		_triangles = triangles;
		_points3D = points3D;

		/* setup the size, position, and display mode for new windows */
		glutInitWindowSize(width, height);
		glutInitWindowPosition(0, 0);
		glutInitDisplayMode(GLUT_RGB);

		/* create and set up a window */
		glutCreateWindow("3D Reconstruction");
		glutDisplayFunc(draw);

		/* define the projection transformation */
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//glOrtho(0.0, 1.0, 0.0, 1, 0.0, 0.0);

		/* define the viewing transformation */
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}

	void RenderService::TestExecute(int *argc, char **argv, vector<Point3f> points)
	{
		PointUtilities *converter = new PointUtilities();

		if (points.size() == 0)
			points = converter->GetMockPoints();

		DelaunayService *delaunay = new DelaunayService();

		Execute(argc, argv, delaunay->Execute(points), points);
	}

	void RenderService::Execute(int *argc, char **argv, vector<Vec6f> triangles, vector<Point3f> points3D)
	{
		glutInit(argc, argv);

		//Init configuratons of screen
		Init(1000, 1000, triangles, points3D);

		/* tell GLUT to wait for events */
		glutMainLoop();
	}
}
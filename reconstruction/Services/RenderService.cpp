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
			Point2f pt1{ triangle[0], triangle[1] };
			Point2f pt2{ triangle[2], triangle[3] };
			Point2f pt3{ triangle[4], triangle[5] };
			
			
			glBegin(GL_LINES);
				glVertex3f(pt1.x/maxAbs, pt1.y/maxAbs * -1, 0);
				glVertex3f(pt2.x/maxAbs, pt2.y/maxAbs * -1, 0);
			glEnd();

			glBegin(GL_LINES);
				glVertex3f(pt2.x / maxAbs, pt2.y / maxAbs * -1, 0);
				glVertex3f(pt3.x / maxAbs, pt3.y / maxAbs * -1, 0);
			glEnd();

			glBegin(GL_LINES);
				glVertex3f(pt3.x / maxAbs, pt3.y / maxAbs * -1, 0);
				glVertex3f(pt1.x / maxAbs, pt1.y / maxAbs * -1, 0);
			glEnd();
			/*
			glPointSize(5.0);
			glBegin(GL_POINTS);
				glVertex3f(pt1.x / maxAbs, pt1.y / maxAbs, 0);
				glVertex3f(pt2.x / maxAbs, pt2.y / maxAbs, 0);
				glVertex3f(pt3.x / maxAbs, pt3.y / maxAbs, 0);
			glEnd();
			*/
		}

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

		Execute(argc, argv, delaunay->Execute(points, points), points);
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
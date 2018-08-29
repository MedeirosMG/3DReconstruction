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

		// Get triangles and points setted
		vector<Vec6f> triangleList = service->GetTriangles();
		vector<Point3f> points = service->GetPoints();

		// Draw triangles
		for (size_t i = 0; i < triangleList.size(); i++) {
			Vec6f triangle = triangleList[i];
			Point pt1{ cvRound(triangle[0]), cvRound(triangle[1]) };
			Point pt2{ cvRound(triangle[2]), cvRound(triangle[3]) };
			Point pt3{ cvRound(triangle[4]), cvRound(triangle[5]) };

			glBegin(GL_TRIANGLES);
				glVertex3f(0, 0, 0);
				glVertex3f(500, 0, 0);
				glVertex3f(500, 500, 0);
				//glVertex3f(pt1.x, pt1.y, 0);
				//glVertex3f(pt2.x, pt2.y, 0);
				//glVertex3f(pt3.x, pt3.y, 0);
			glEnd();

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
		glViewport(0, 0, width, height);

		/* create and set up a window */
		glutCreateWindow("3D Reconstruction");
		glutDisplayFunc(draw);

		/* define the projection transformation */
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, width, 0.0, height, 0.0, 0.0);

		/* define the viewing transformation */
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}

	void RenderService::TestExecute(int *argc, char **argv, vector<CustomPoint> points, int zoom)
	{
		PointUtilities *converter = new PointUtilities();

		if (points.size() == 0)
			points = converter->GetMockPoints();

		DelaunayService *delaunay = new DelaunayService();

		Execute(argc, argv, delaunay->Execute(points, zoom), points, zoom);
	}

	void RenderService::Execute(int *argc, char **argv, vector<Vec6f> triangles, vector<CustomPoint> points3D, int zoom)
	{
		glutInit(argc, argv);
	
		//Convert Points
		PointUtilities *converter = new PointUtilities();
		vector<Point3f> _points = converter->ReturnPoint3f(points3D);

		_points = converter->PointsZoom(_points, zoom);

		// Get max width and max height of points
		float maxWidth = converter->GetMaxAbsCoord(_points, "x");
		float maxHeight = converter->GetMaxAbsCoord(_points, "y");
		float maxAbs = 0.0;

		if (maxWidth > maxHeight)
			maxAbs = maxWidth;
		else if (maxHeight > maxWidth)
			maxAbs = maxHeight;

		// Update values of points
		_points = converter->PointsTranslocate(_points, maxAbs);

		//Init configuratons of screen
		Init(converter->GetMaxAbsCoord(_points, "x") + 10, converter->GetMaxAbsCoord(_points, "y") + 10, triangles, _points);

		/* tell GLUT to wait for events */
		glutMainLoop();
	}
}
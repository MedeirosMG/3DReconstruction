#include "stdafx.h"
#include "RenderService.h"

namespace Services {
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
		glutWireTeapot(.5);
		
		glFlush();
	}

	void RenderService::Init() 
	{
		/* setup the size, position, and display mode for new windows */
		glutInitWindowSize(500, 500);
		glutInitWindowPosition(0, 0);
		glutInitDisplayMode(GLUT_RGB);


		/* create and set up a window */
		glutCreateWindow("3D Reconstruction");
		glutDisplayFunc(draw);

		/* define the projection transformation */
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

		/* define the viewing transformation */
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}

	void RenderService::Execute(int *argc, char **argv, vector<Vec6f> triangles, vector<CustomPoint> points3D)
	{
		glutInit(argc, argv);
	
		//Init configuratons of screen
		Init();

		/* tell GLUT to wait for events */
		glutMainLoop();
	}
}
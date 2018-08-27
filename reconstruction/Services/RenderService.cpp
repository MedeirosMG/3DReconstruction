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

	void display(void) {
		
		glutSolidTeapot(40.0);
	}

	void RenderService::Execute(int *argc, char **argv)
	{
		glutInit(argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGB);
		glutInitWindowPosition(500, 500);
		glutInitWindowSize(800, 600);
		glutCreateWindow("OpenGL First Window");

		glEnable(GL_DEPTH_TEST);
		glClearColor(1.0, 0.0, 0.0, 1.0);
		// register callbacks
		glutDisplayFunc(display);

		glutMainLoop();
	}
}
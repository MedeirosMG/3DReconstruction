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
		
		//glutSolidTeapot(40.0);
		glClear(GL_COLOR_BUFFER_BIT);

		/* draw white polygon (rectangle) with corners at

		* (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)

		*/

		glColor3f(0.50, 0.40, 0.0);

		glBegin(GL_POLYGON);

		glVertex3f(0.25, 0.25, 0.0);

		glVertex3f(0.75, 0.25, 0.0);

		glVertex3f(0.75, 0.75, 0.0);

		glVertex3f(0.25, 0.75, 0.0);

		glEnd();


		/* don't wait!

		* start processing buffered OpenGL routines

		*/

		glFlush();
	}
	void init() {
		glClearColor(0.0, 0.0, 0.0, 0.0);

		/* initialize viewing values */

		glMatrixMode(GL_PROJECTION);

		glLoadIdentity();

		glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	}

	void RenderService::Execute(int *argc, char **argv)
	{

		glutInit(argc, argv);

		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

		glutInitWindowSize(250, 250);

		glutInitWindowPosition(100, 100);

		glutCreateWindow("hello");

		init();

		glutDisplayFunc(display);

		glutMainLoop();
	}
}
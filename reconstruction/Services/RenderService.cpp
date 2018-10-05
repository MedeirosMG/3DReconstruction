#include "stdafx.h"
#include "RenderService.h"

namespace Services {
	// Static variables
	RenderProperties *RenderService::_renderProperties;
	//-//-//

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

	void checkKeyboard(unsigned char key, int x, int y) {

		RenderService *service = new RenderService();

		if (key == 'L' || key == 'l') {
			service->_renderProperties->_typeImage = 1;
		}
		else if (key == 'T' || key == 't') {
			service->_renderProperties->_typeImage = 2;
		}
		else if (key == 'P' || key == 'p') {
			service->_renderProperties->_typeImage = 3;
		}

		glutPostRedisplay();
	}

	void drawText(const char *text, int length, int x, int y) {
		glColor3f(255.0, 255.0, 255.0);
		glMatrixMode(GL_PROJECTION);
		double *matrix = new double[16];
		glGetDoublev(GL_PROJECTION_MATRIX, matrix);
		glLoadIdentity();
		glOrtho(0, 800, 0, 600, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		glLoadIdentity();
		glRasterPos2i(x, y);
		for (int i = 0; i < length; i++)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixd(matrix);
		glMatrixMode(GL_MODELVIEW);
	}

	void DrawImage(void) {
		RenderService *service = new RenderService();
		PointUtilities *converter = new PointUtilities();

		float maxAbs = converter->GetMaxAbsCoord(service->_renderProperties->_triangles);

		if (service->_renderProperties->_typeImage == 1)
			glBegin(GL_LINES);
		else if (service->_renderProperties->_typeImage == 2)
			glBegin(GL_TRIANGLES);
		else if (service->_renderProperties->_typeImage == 3)
			glBegin(GL_POINTS);

		for each (Vec<Point3f,3> triangle in service->_renderProperties->_triangles)
		{
			Point3f pt1 = triangle[0];
			Point3f pt2 = triangle[1];
			Point3f pt3 = triangle[2];

			switch (service->_renderProperties->_typeImage)
			{
				case 1:
					glVertex3f(pt1.x / maxAbs, pt1.y / maxAbs, pt1.z / maxAbs);
					glVertex3f(pt2.x / maxAbs, pt2.y / maxAbs, pt2.z / maxAbs);

					glVertex3f(pt2.x / maxAbs, pt2.y / maxAbs, pt2.z / maxAbs);
					glVertex3f(pt3.x / maxAbs, pt3.y / maxAbs, pt3.z / maxAbs);

					glVertex3f(pt3.x / maxAbs, pt3.y / maxAbs, pt3.z / maxAbs);
					glVertex3f(pt1.x / maxAbs, pt1.y / maxAbs, pt1.z / maxAbs);
					break;

				case 2:
				case 3:
					glVertex3f(pt1.x / maxAbs, pt1.y / maxAbs, pt1.z / maxAbs);
					glVertex3f(pt2.x / maxAbs, pt2.y / maxAbs, pt2.z / maxAbs);
					glVertex3f(pt3.x / maxAbs, pt3.y / maxAbs, pt3.z / maxAbs);
					break;
					
				default:
					string text = "Desenhar com: L = linhas | T = Triangulos | P = Pontos";
					glColor3b(0, 1, 0);
					drawText(text.data(), text.size(), 20, 20);
					text = "Utilize as setas para rotacionar o objeto";
					drawText(text.data(), text.size(), 20, 40);
					break;
			}
		}

		glEnd();
	}

	void SpecialKeys(int key, int x, int y)
	{
		RenderService *service = new RenderService();
		if (key == GLUT_KEY_UP) {
			service->_renderProperties->_RotationDegree -= 10.0;
			service->_renderProperties->_rotateY = 0;
			service->_renderProperties->_rotateX = 1;
			service->_renderProperties->_rotate = true;
		}
		else if (key == GLUT_KEY_DOWN) {
			service->_renderProperties->_RotationDegree += 10.0;
			service->_renderProperties->_rotateY = 0;
			service->_renderProperties->_rotateX = 1;
			service->_renderProperties->_rotate = true;
		}
		else if (key == GLUT_KEY_RIGHT) {
			service->_renderProperties->_RotationDegree -= 10.0;
			service->_renderProperties->_rotateY = 1;
			service->_renderProperties->_rotateX = 0;
			service->_renderProperties->_rotate = true;
		}
		else if (key == GLUT_KEY_LEFT) {
			service->_renderProperties->_RotationDegree += 10.0;
			service->_renderProperties->_rotateY = 1;
			service->_renderProperties->_rotateX = 0;
			service->_renderProperties->_rotate = true;
		}

		glutPostRedisplay();
	}


	void Draw(void) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(1.0, 1.0, 1.0);

		RenderService *service = new RenderService();
		
		// Rotate image
		if (service->_renderProperties->_rotate) {
			glRotated(service->_renderProperties->_RotationDegree, service->_renderProperties->_rotateX, service->_renderProperties->_rotateY, 0);
			service->_renderProperties->_rotate = false;
		}

		// Draw new image
		DrawImage();

		string text = "Desenhar com: L = linhas | T = Triangulos | P = Pontos";
		glColor3b(0, 1, 0);
		drawText(text.data(), text.size(), 20, 20);
		text = "Utilize as setas para rotacionar o objeto";
		drawText(text.data(), text.size(), 20, 40);

		glFlush();
	}

	void RenderService::Init(int width, int height, vector<Vec6f> triangles, vector<Point3f> points3D)
	{
		// Set render properties
		_renderProperties = new RenderProperties(10);

		// Convert points
		_renderProperties->_triangles = Convert().Tiangles2dTo3d(triangles, points3D);

		/* setup the size, position, and display mode for new windows */
		glutInitWindowSize(width, height);
		glutInitWindowPosition(0, 0);
		glutInitDisplayMode(GLUT_RGB);

		/* create and set up a window */
		glutCreateWindow("3D Reconstruction");
		glutDisplayFunc(Draw);

		/* define the projection transformation */
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//glOrtho(0.0, 1.0, 0.0, 1, 0.0, 0.0);

		/* define the viewing transformation */
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Control funcs
		glutKeyboardFunc(checkKeyboard);
		glutSpecialFunc(SpecialKeys);
	}

	void RenderService::TestExecute(int *argc, char **argv, vector<Point3f> points)
	{
		PointUtilities *converter = new PointUtilities();

		if (points.size() == 0)
			points = converter->GetMockPoints();

		DelaunayService *delaunay = new DelaunayService();

		Execute(argc, argv, delaunay->Execute(points, vector<Point3f>()), points);
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
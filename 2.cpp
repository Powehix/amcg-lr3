#include<Windows.h>
#include <GL/glut.h>
#include<vector>
#include<fstream>
#include <cstdlib>
using namespace std;

struct Point
{
	GLfloat x, y;
};

void reshape(int w, int h);
void display();
void displayA();
void displayM();
void readFromFileA();
void readFromFileM();
void linetoA(Point p);
void linetoM(Point p);
void movetoA(Point p);
void movetoM(Point p);
vector<Point> pointsA;
vector<Point> pointsM;
vector<int>codeA;
vector<int>codeM;
Point currentPointA;
Point currentPointM;
Point centerA;
Point centerM;

int angleX = 0;

void processNormalKeys(unsigned char key, int x, int y);
void processSpecialKeys(int key, int x, int y);

int main(int argc, char * argv[])
{
	currentPointA.x = 0; currentPointA.y = 0;
	currentPointM.x = 0; currentPointM.y = 0;
	centerA.x = 0; centerA.y = 0;
	centerM.x = 0; centerM.y = 0;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("PW4_2");


	glClearColor(1, 1, 1, 0);
	glShadeModel(GL_FLAT);
	glEnable(GL_MAP1_VERTEX_3);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMainLoop();
	return 0;
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0, 150, 0, 70);
	gluOrtho2D(-30, 200, -10, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	displayA();
	displayM();
	glutSwapBuffers();
	glFlush();
}


void displayA()
{
	readFromFileA();
	glColor3d(1, 0, 0);
	for (int i = 0; i < codeA.size(); i++) {
		if (codeA[i] < 0)
			movetoA(pointsA[abs(codeA[i]) - 1]);
		else {
			linetoA(pointsA[codeA[i] - 1]);
		}
	}
	glFlush();

}

void displayM()
{
	readFromFileM();
	glColor3d(1, 0, 0);
	for (int i = 0; i < codeM.size(); i++) {
		if (codeM[i] < 0)
			movetoM(pointsM[abs(codeM[i]) - 1]);
		else {
			linetoM(pointsM[codeM[i] - 1]);
		}
	}
	glFlush();
}

Point getCenterA() {
	return centerA;
}

Point getCenterM() {
	return centerM;
}


void readFromFileA()
{
	fstream f("A.txt", ios::in);
	int pointNumber;
	int x, y; Point p;
	f >> pointNumber;
	for (int i = 0; i < pointNumber; i++)
	{
		f >> p.x >> p.y;
		pointsA.push_back(p);
	}

	int movesNumber, m;
	f >> movesNumber;
	for (int i = 0; i < movesNumber; i++)
	{
		f >> m; codeA.push_back(m);
	}
	f.close();

	Point minPointA = pointsA[abs(codeA[0]) - 1], maxPointA = pointsA[abs(codeA[0]) - 1];
	for (int i = 1; i < movesNumber; i++) {
		const Point p = pointsA[abs(codeA[i]) - 1];
		if (p.x < minPointA.x) {
			minPointA.x = p.x;
		}
		if (p.y < minPointA.y) {
			minPointA.y = p.y;
		}
		if (p.x > maxPointA.x) {
			maxPointA.x = p.x;
		}
		if (p.y > maxPointA.y) {
			maxPointA.y = p.y;
		}
	}

	centerA.x = (maxPointA.x + minPointA.x) / 2;
	centerA.y = (maxPointA.y + minPointA.y) / 2;
}

void readFromFileM()
{
	fstream f("M.txt", ios::in);
	int pointNumber;
	int x, y; Point p;
	f >> pointNumber;
	for (int i = 0; i < pointNumber; i++)
	{
		f >> p.x >> p.y;
		pointsM.push_back(p);
	}

	int movesNumber, m;
	f >> movesNumber;
	for (int i = 0; i < movesNumber; i++)
	{
		f >> m; codeM.push_back(m);
	}
	f.close();

	Point minPointM = pointsM[abs(codeM[0]) - 1], maxPointM = pointsM[abs(codeM[0]) - 1];
	for (int i = 1; i < movesNumber; i++) {
		const Point p = pointsM[abs(codeM[i]) - 1];
		if (p.x < minPointM.x) {
			minPointM.x = p.x;
		}
		if (p.y < minPointM.y) {
			minPointM.y = p.y;
		}
		if (p.x > maxPointM.x) {
			maxPointM.x = p.x;
		}
		if (p.y > maxPointM.y) {
			maxPointM.y = p.y;
		}
	}

	centerM.x = (maxPointM.x + minPointM.x) / 2;
	centerM.y = (maxPointM.y + minPointM.y) / 2;
}


void movetoA(Point p) {
	currentPointA.x = p.x; currentPointA.y = p.y;

}
void movetoM(Point p2) {
	currentPointM.x = p2.x; currentPointM.y = p2.y;
}

void linetoA(Point p) {
	glBegin(GL_LINES);
	glVertex2i(currentPointA.x, currentPointA.y);
	glVertex2i(p.x, p.y);
	glEnd();
	currentPointA.x = p.x; currentPointA.y = p.y;
}

void linetoM(Point p) {
	glBegin(GL_LINES);
	glVertex2i(currentPointM.x, currentPointM.y);
	glVertex2i(p.x, p.y);
	glEnd();
	currentPointM.x = p.x; currentPointM.y = p.y;
}

void processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 27)   //если нажать 'Esc' (код по таблице ASCII)
		exit(0);
	if (key == 43)   //если нажать '+'
	{
		glMatrixMode(GL_MODELVIEW);
		glScalef(1.3, 1.3, 1);
		display();
	}
	if (key = 45)   //если нажать '-'
	{
		glMatrixMode(GL_MODELVIEW);
		glScalef(0.9, 0.9, 1);
		display();
	}
}

void processSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		glMatrixMode(GL_MODELVIEW);
		glTranslated(0, 2, 0);
		display();
		break;
	case GLUT_KEY_DOWN:
		glMatrixMode(GL_MODELVIEW);
		glTranslated(0, -2, 0);
		display();
		break;
	case GLUT_KEY_LEFT:
		glMatrixMode(GL_MODELVIEW);
		glTranslated(-2, 0, 0);
		display();
		break;
	case GLUT_KEY_RIGHT:
		glMatrixMode(GL_MODELVIEW);
		glTranslated(2, 0, 0);
		display();
		break;
	case GLUT_KEY_HOME:   //вращение против часовой стрелки
		glMatrixMode(GL_MODELVIEW);
		glRotatef(1, 0, 0, 1);
		display();
		break;
	case GLUT_KEY_END:   //вращение по часовой стрелки
		glMatrixMode(GL_MODELVIEW);
		glRotatef(-1, 0, 0, 1);
		display();
		break;
	case GLUT_KEY_PAGE_UP:   //вращение двух букв в протиположные стороны
		angleX += 2;

		glMatrixMode(GL_MODELVIEW);
		Point A = getCenterA();
		glPushMatrix();
		glClearColor(1, 1, 1, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		glTranslated(A.x, A.y, 0);
		glRotatef(angleX, 0, 0, 1);
		glTranslated(-A.x, -A.y, 0);
		displayA();
		glPopMatrix();

		Point M = getCenterM();
		glPushMatrix();
		glTranslated(M.x, M.y, 0);
		glRotatef(-angleX, 0, 0, 1);
		glTranslated(-M.x, -M.y, 0);
		displayM();
		glPopMatrix();
		break;
	}
}

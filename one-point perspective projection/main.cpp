
#include<gl/glut.h>

#include<windows.h>

#include<iostream>

#include<algorithm>

#include<cmath>

using namespace std;



const int MAXN = 200;

int winWidth = 1000, winHeight = 600;

int MyPointNum = 0; 

double PI = acos(-1.0);

double Matrix[4][4] = { {1,0,0,0},{0,1,0,0},{0,0,1,0},{500,300,300,1} };

double dd = -500, nn = -400, mm = -320, ll = 160;

double T1[4][4] = { {1,0,0,0},{0,1,0,0},{0,0,0,1 / dd},{ll,mm,0,1 + nn / dd} };

struct point

{

	double x, y, z, tag;

}MyPoint[MAXN], TPoint[MAXN];

void T1Init()

{

	T1[0][0] = 1;    T1[0][1] = 0;   T1[0][2] = 0;     T1[0][3] = 0;

	T1[1][0] = 0;    T1[1][1] = 1;   T1[1][2] = 0;     T1[1][3] = 0;

	T1[2][0] = 0;    T1[2][1] = 0;   T1[2][2] = 0;     T1[2][3] = 1 / dd;

	T1[3][0] = ll;   T1[3][1] = mm;  T1[3][2] = 0;     T1[3][3] = 1 + nn / dd;

}



void MyPologyInit()

{

	MyPointNum = 8;

	MyPoint[0].x = 0, MyPoint[0].y = 0, MyPoint[0].z = 0, MyPoint[0].tag = 1;

	MyPoint[1].x = 200, MyPoint[1].y = 0, MyPoint[1].z = 0, MyPoint[1].tag = 1;

	MyPoint[2].x = 200, MyPoint[2].y = 200, MyPoint[2].z = 0, MyPoint[2].tag = 1;

	MyPoint[3].x = 0, MyPoint[3].y = 200, MyPoint[3].z = 0, MyPoint[3].tag = 1;



	MyPoint[4].x = 0, MyPoint[4].y = 0, MyPoint[4].z = 200, MyPoint[4].tag = 1;

	MyPoint[5].x = 200, MyPoint[5].y = 0, MyPoint[5].z = 200, MyPoint[5].tag = 1;

	MyPoint[6].x = 200, MyPoint[6].y = 200, MyPoint[6].z = 200, MyPoint[6].tag = 1;

	MyPoint[7].x = 0, MyPoint[7].y = 200, MyPoint[7].z = 200, MyPoint[7].tag = 1;

}

void MyTrans(point NewPoint[], point OldPoint[], double Tran[4][4])

{

	for (int i = 0; i < MyPointNum; i++)

	{

		double tx = OldPoint[i].x, ty = OldPoint[i].y, tz = OldPoint[i].z, ttag = OldPoint[i].tag;

		NewPoint[i].x = tx * Tran[0][0] + ty * Tran[1][0] + tz * Tran[2][0] + ttag * Tran[3][0];

		NewPoint[i].y = tx * Tran[0][1] + ty * Tran[1][1] + tz * Tran[2][1] + ttag * Tran[3][1];

		NewPoint[i].z = tx * Tran[0][2] + ty * Tran[1][2] + tz * Tran[2][2] + ttag * Tran[3][2];

		NewPoint[i].tag = tx * Tran[0][3] + ty * Tran[1][3] + tz * Tran[2][3] + ttag * Tran[3][3];

		if (NewPoint[i].tag != 0 && NewPoint[i].tag != 1)

		{

			NewPoint[i].x /= NewPoint[i].tag, NewPoint[i].y /= NewPoint[i].tag, NewPoint[i].z /= NewPoint[i].tag, NewPoint[i].tag = 1;

		}

	}

}


void ChangeSize(int w, int h)

{

	winWidth = w; winHeight = h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluOrtho2D(0.0, winWidth, 0.0, winHeight);

}

void OnDraw(point TmpPoint[])

{

	glColor3f(0.0f, 1.0f, 0.0f);

	glBegin(GL_LINES);

	glVertex2d(TmpPoint[0].x, TmpPoint[0].y);  glVertex2d(TmpPoint[1].x, TmpPoint[1].y);

	glVertex2d(TmpPoint[0].x, TmpPoint[0].y);  glVertex2d(TmpPoint[3].x, TmpPoint[3].y);

	glVertex2d(TmpPoint[0].x, TmpPoint[0].y);  glVertex2d(TmpPoint[4].x, TmpPoint[4].y);

	glVertex2d(TmpPoint[1].x, TmpPoint[1].y);  glVertex2d(TmpPoint[0].x, TmpPoint[0].y);

	glVertex2d(TmpPoint[1].x, TmpPoint[1].y);  glVertex2d(TmpPoint[2].x, TmpPoint[2].y);

	glVertex2d(TmpPoint[1].x, TmpPoint[1].y);  glVertex2d(TmpPoint[5].x, TmpPoint[5].y);

	glVertex2d(TmpPoint[2].x, TmpPoint[2].y);  glVertex2d(TmpPoint[1].x, TmpPoint[1].y);

	glVertex2d(TmpPoint[2].x, TmpPoint[2].y);  glVertex2d(TmpPoint[3].x, TmpPoint[3].y);

	glVertex2d(TmpPoint[2].x, TmpPoint[2].y);  glVertex2d(TmpPoint[6].x, TmpPoint[6].y);

	glVertex2d(TmpPoint[3].x, TmpPoint[3].y);  glVertex2d(TmpPoint[0].x, TmpPoint[0].y);

	glVertex2d(TmpPoint[3].x, TmpPoint[3].y);  glVertex2d(TmpPoint[2].x, TmpPoint[2].y);

	glVertex2d(TmpPoint[3].x, TmpPoint[3].y);  glVertex2d(TmpPoint[7].x, TmpPoint[7].y);

	glVertex2d(TmpPoint[4].x, TmpPoint[4].y);  glVertex2d(TmpPoint[5].x, TmpPoint[5].y);

	glVertex2d(TmpPoint[5].x, TmpPoint[5].y);  glVertex2d(TmpPoint[6].x, TmpPoint[6].y);

	glVertex2d(TmpPoint[6].x, TmpPoint[6].y);  glVertex2d(TmpPoint[7].x, TmpPoint[7].y);

	glVertex2d(TmpPoint[7].x, TmpPoint[7].y);  glVertex2d(TmpPoint[4].x, TmpPoint[4].y);

	glEnd();



	//Çó½»µã

	double x1_x0 = TmpPoint[4].x - TmpPoint[0].x;

	double y1_y0 = TmpPoint[4].y - TmpPoint[0].y;

	double x4_x3 = TmpPoint[5].x - TmpPoint[1].x;

	double y4_y3 = TmpPoint[5].y - TmpPoint[1].y;

	double cro_x = (y4_y3*x1_x0*TmpPoint[1].x + (TmpPoint[0].y - TmpPoint[1].y)*x4_x3*x1_x0 - x4_x3 * y1_y0*TmpPoint[0].x) / ((x1_x0*y4_y3) - (x4_x3)*(y1_y0));

	double cro_y = y4_y3 * (cro_x - TmpPoint[1].x) / x4_x3 + TmpPoint[1].y;



	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_LINES);

	glVertex2d(TmpPoint[0].x, TmpPoint[0].y);   glVertex2d(cro_x, cro_y);

	glVertex2d(TmpPoint[1].x, TmpPoint[1].y);   glVertex2d(cro_x, cro_y);

	glVertex2d(TmpPoint[2].x, TmpPoint[2].y);   glVertex2d(cro_x, cro_y);

	glVertex2d(TmpPoint[3].x, TmpPoint[3].y);   glVertex2d(cro_x, cro_y);

	glEnd();

}

void GetProcess()

{

	T1Init();

	MyTrans(TPoint, MyPoint, T1);

	MyTrans(TPoint, TPoint, Matrix);

}

void Display()

{

	glClear(GL_COLOR_BUFFER_BIT);

	GetProcess();

	OnDraw(TPoint);

	glutSwapBuffers();

}

void MyInit()

{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	MyPologyInit();

	dd = -500, nn = -400, mm = -320, ll = 160;

}

void SpecialKeys(int key, int x, int y)

{

	if (key == GLUT_KEY_UP)dd -= 100;

	if (key == GLUT_KEY_DOWN)dd += 100;

	glutPostRedisplay();

}



int main(int argc, char* argv[])

{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(1000, 600);

	glutInitWindowPosition(0, 0);

	glutCreateWindow("one-point perspective projection");

	glutDisplayFunc(Display);

	glutReshapeFunc(ChangeSize);

	glutSpecialFunc(SpecialKeys);

	MyInit();

	glutMainLoop();

	return 0;
}
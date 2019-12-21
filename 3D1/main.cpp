//#include "stdafx.h"
#include<GL/freeglut.h>
#include<GLFW/glfw3.h>

#include <stdio.h>

#include <comutil.h>

#include <gl/glut.h>

#pragma comment(lib, "glut32.lib")

#ifdef _DEBUG

#pragma comment(lib, "comsuppwd.lib")

#else

#pragma comment(lib, "comsuppw.lib")

#endif



COLORREF m_FontColor = RGB(255, 128, 255);



void DrawString(int x, int y, char *strText)

{

	HDC hDC = wglGetCurrentDC();



	int xx = m_FontColor;

	float r = GetRValue(m_FontColor) / 255.0f;

	float g = GetGValue(m_FontColor) / 255.0f;

	float b = GetBValue(m_FontColor) / 255.0f;

	glColor3f(r, g, b);

	glRasterPos2i(x, y);

	int ListNum;

	DWORD dwChar;

	unsigned char *text = (unsigned char*)strText;

	glPushAttrib(GL_LIST_BIT);		// Pushes The Display List Bits  

	for (size_t i = 0; i < strlen(strText); i++)

	{

		if (IsDBCSLeadByte(text[i]))	//是双字节字符吗？(用于汉字处理)  

		{

			char tmpchar[3];

			tmpchar[0] = text[i];

			tmpchar[1] = text[i + 1];

			tmpchar[2] = 0;

			BSTR xx = _com_util::ConvertStringToBSTR(tmpchar); //转化为unicode字符  

			BYTE tmpchr[2];

			::CopyMemory(tmpchr, xx, 2);

			dwChar = tmpchr[0] + tmpchr[1] * 256;

			i++;

		}

		else

		{

			dwChar = text[i];

		}

		ListNum = glGenLists(1);

		BOOL ret = FALSE;

		ret = wglUseFontBitmapsW(hDC, dwChar, 1, ListNum);

		glCallList(ListNum);

		glDeleteLists(ListNum, 1);

	}

	glPopAttrib();

}



void MyDrawString(int nSize, TCHAR *string)

{

	HDC hDC = wglGetCurrentDC();

	HFONT hOldFont, hFont;

	int nLength;

	wchar_t dwChar[256];

	GLuint ListNum;



	hFont = ::CreateFont(nSize, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, 0,

		GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("宋体"));

	hOldFont = (HFONT)::SelectObject(hDC, hFont);

	nLength = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, string, -1, dwChar, 256);

	for (int i = 0; i < nLength - 1; i++)

	{

		ListNum = glGenLists(1);

		wglUseFontBitmapsW(hDC, dwChar[i], 1, ListNum); //W表示BSTR  

		glCallList(ListNum);

		glDeleteLists(ListNum, 1);

	}

	::SelectObject(hDC, hOldFont);

	::DeleteObject(hFont);

}

static void init()

{

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glShadeModel(GL_FLAT);

	glEnable(GL_DEPTH_TEST);

}



void reshape(int w, int h)

{

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 30.0);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	glTranslatef(0.0, 0.0, -3.6f);

}




void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 三维图形由三维空间中的三角形拼接而成
	glBegin(GL_TRIANGLES);

	// 指定棱锥的四个顶点
	GLfloat vertex[4][3] = {
		{0, 0, 0.5},
		{0.2, 0.2, 0},
		{-0.3, 0, 0},
		{0, -0.3, 0}
	};

	// 绘制三角形
	glColor3f(0.2, 0.2, 0.8);
	for (int i = 0; i < 2; i++) {
		for (int j = i + 1; j < 3; j++) {
			for (int k = j + 1; k < 4; k++) {
				glVertex3fv(vertex[i]);
				glVertex3fv(vertex[j]);
				glVertex3fv(vertex[k]);
			}
		}
	}

	glEnd();

	// 绘制顶点连线
	glBegin(GL_LINES);

	glColor3f(1, 0, 0);
	for (int i = 0; i < 3; i++)
	{
		for (int j = i + 1; j < 4; j++) {
			glVertex3fv(vertex[i]);
			glVertex3fv(vertex[j]);
		}
	}

	glEnd();
	glFlush();
	

	

	DrawString(0.0, 0.0, "顶点个数：4    三角形个数：3");



	glFlush();

}
void input(int argc, char **argv)

{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

	glutCreateWindow(argv[0]);

	glutInitWindowPosition(100, 100);

	glutInitWindowSize(400, 400);

	init();

	glutReshapeFunc(reshape);

	glutDisplayFunc(display);



	glutMainLoop();

}

int main()
{
	glfwInit();
	

	GLFWwindow* window = glfwCreateWindow(400, 400, "3D", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(10);
	while (glfwWindowShouldClose(window) == GL_FALSE)
	{
		// 绘制棱锥
		display();

		glfwSwapBuffers(window);
		glfwPollEvents();
		
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	

	
	return 0;
}


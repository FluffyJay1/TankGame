#include "Utilities.h"
#include "FrameworkInterface.h"
#include "InputManager.h"
#include <stdio.h>
#include <time.h>
int winID;
void loop(void)
{
	glutPostRedisplay();
	UpdateInputManager();
}

void frameworkUpdate(void)
{
	FrameBuffer_ClearToBackground(&GlobalFrameBuffer);
	render();
	
	glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, GlobalFrameBuffer.buffer);
	glutSwapBuffers();
}

void init(void)
{  
	InitInputManager();
	FrameBuffer_Init(&GlobalFrameBuffer,WIDTH, HEIGHT);
  Init();
}

//Lock the window to the initial WIDTH and HEIGHT
void reshape(int newX, int newY)
{
	if (newX != WIDTH || newY != HEIGHT)
	{
		glutReshapeWindow(WIDTH, HEIGHT);
	}
	
}

int main (int argc, char **argv)
{
  srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	winID = glutCreateWindow("VGP3");
	glutReshapeFunc(reshape);

	glClearColor(0, 0, 0, 1);	

	//glutKeyboardFunc(keyboard);
	glutDisplayFunc(frameworkUpdate);
	glutIdleFunc(loop);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);

	init();

	glutMainLoop();
	return 0;
}


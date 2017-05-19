/* 
	* Author: Manjunath M
	* Email: manjunath.bsk3@gmail.com
*/
#include"Events.h"
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GL_DOUBLE | GL_RGBA);
	glutInitWindowSize(700,700);
	glutInitWindowPosition(250, 15);
	glutCreateWindow("Checkers Game");
	glutReshapeFunc(reshape_event_handler);
	glutDisplayFunc(display_event_handler);
	glutMouseFunc(mouse_event_handler);
	glutKeyboardFunc(keyboard_event_handler);
	glutCreateMenu(popupmenu_handler);
	glutAddMenuEntry("Toggle Fullscreen [F/f]",1);
	glutAddMenuEntry("Restart Game [R/r]",3);
	glutAddMenuEntry("Exit/Quit [Q/q]",4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}
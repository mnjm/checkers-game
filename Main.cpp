/* 
	* Author: Manjunath M
	* Email: manjunath.bsk3@gmail.com
*/
#include"Events.h"
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(700,700);
	glutInitWindowPosition(333,35);
	glutCreateWindow("Checkers Game");
	glutReshapeFunc(reshape_event_handler);
	glutDisplayFunc(display_event_handler);
	glutMouseFunc(mouse_event_handler);
	glutKeyboardFunc(keyboard_event_handler);
	glutMainLoop();
	return 0;
}

#include"Events.h"
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GL_DOUBLE | GL_RGBA);
	glutInitWindowSize(700,700);
	glutInitWindowPosition(15, 15);
	glutCreateWindow("Checker's Game");
	glutReshapeFunc(reshape_event_handler);
	glutDisplayFunc(display_event_handler);
	glutMouseFunc(mouse_event_handler);
	glutKeyboardFunc(keyboard_event_handler);
	glutMainLoop();
	return 0;
}
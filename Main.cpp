#include"Events.h"
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GL_DOUBLE | GL_RGBA);
	glutInitWindowSize(700,700);
	glutInitWindowPosition(15, 15);
	glutCreateWindow("Checkers Game");
	glutReshapeFunc(reshape_event_handler);
	glutDisplayFunc(display_event_handler);
	glutMouseFunc(mouse_event_handler);
	glutKeyboardFunc(keyboard_event_handler);
	glutCreateMenu(popupmenu_handler);
	glutAddMenuEntry("Enter Fullscreen",1);
	glutAddMenuEntry("Leave Fullscreen",2);
	glutAddMenuEntry("Restart Game",3);
	glutAddMenuEntry("Exit/Quit",4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	/*Testing*/ //glutTimerFunc(30,rotate_the_board,0);
	glutMainLoop();
	return 0;
}
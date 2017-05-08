#include"Objects.h"
#include<math.h>
#include<iostream>
bool is_first_time = true;
Board board_obj;
Pawn pawns[24];
extern int board[8][4]; // Defined in Objects.h Header file.
void init()
{
	int count = 0;
	// Player 1
	for(int i = 0; i<4 ; i++)
	{
		pawns[count++].create_pawn(0, i, 1);
		pawns[count++].create_pawn(1, i, 1);
		pawns[count++].create_pawn(2, i, 1);
		pawns[count++].create_pawn(5, i, 2);
		pawns[count++].create_pawn(6, i, 2);
		pawns[count++].create_pawn(7, i, 2);
	}
}
void display_event_handler()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	board_obj.draw();
	if(is_first_time) { init(); is_first_time = false; }
	for(int i = 0; i<24; i++)
		pawns[i].draw();
	glutSwapBuffers(); //Swapping Back and Front Buffers.
}
void reshape_event_handler(int w,int h)
{
	GLint x = 0,y = 0;
	if( w < 700 || h < 700)
		std::cerr<<"Don't Reduce the Window Size\n";
	else
	{
		x = w / 2 - 350;
		y = h / 2 - 350;
	}
	glViewport(x,0,700,700);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-40,40,-40,50);
	glMatrixMode(GL_MODELVIEW);
}
void keyboard_event_handler(unsigned char ch,int x,int y)
{
	if ( ch == 'q' || ch == 'Q' ) exit(0);
	else if ( ch == 'r' || ch == 'R' ) init();
}
void mouse_event_handler(int button,int action,int x,int y)
{
}
#include"Objects.h"
#include<math.h>
#include<iostream>
GLfloat rotate_angle = 0.0f;
bool is_rotating = false;
bool is_first_time = true;
Board board_obj;
Pawn pawns[24];
int board[8][4] = {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}};
void init()
{
	int count = 0;
	for(int i = 0; i<4 ; i++)
	{
		// Player 1 Pawns
		pawns[count].create_pawn( i, 0, 1); board[0][i] = count++;
		pawns[count].create_pawn( i, 1, 1); board[1][i] = count++;
		pawns[count].create_pawn( i, 2, 1); board[2][i] = count++;
		// Player 2 Pawns
		pawns[count].create_pawn( i, 5, 2); board[5][i] = count++;
		pawns[count].create_pawn( i, 6, 2); board[6][i] = count++;
		pawns[count].create_pawn( i, 7, 2); board[7][i] = count++;
	}
	/* Testing [Remove this line] ------------------*/ //pawns[2].create_pawn( 0, 3, 1);
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
void rotate_function()
{
	is_rotating = true; 
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
	glViewport(x,y,700,700);
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
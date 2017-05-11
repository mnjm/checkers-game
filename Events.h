#include"Objects.h"
#include<math.h>
#include<iostream>
bool is_rotating = false;
bool is_first_time = true;
GLint window_width,window_height,window_start_x,window_start_y;
Board board_obj;
Score_Board score_board_obj;
Pawn pawns[24];
int pawn_selected[2] = {-1,-1};
bool is_player2_s_turn = false;
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
	//pawns[3].king_pawn = true;
}
void display_event_handler()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	if(!is_rotating) {}
	board_obj.draw();
	if(is_first_time) { init(); is_first_time = false; }
	for(int i = 0; i<24; i++)
		pawns[i].draw();
	score_board_obj.draw();
	glutSwapBuffers(); //Swapping Back and Front Buffers.
}
void reshape_event_handler(int w,int h)
{
	window_width = w; window_height = h;
	if( w < 700 || h < 700)
		std::cerr<<"Don't Reduce the Window Size\n";
	else
	{
		window_start_x = w / 2 - 350;
		window_start_y = h / 2 - 350;
	}
	glViewport(window_start_x,window_start_y,700,700);
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
	if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
	{
		x-= window_start_x;
		y = window_height -y; y-= window_start_y;
		int i = (int)floor(y / (77.777777777777777));
		int j = (int)floor(x / 87.5);
		if( i%2 == 0)
		{
			if(j%2 == 1) { std::cout<<"Wrong Move\n"; return;}
			j = j / 2;
		}
		else
		{
			if(j%2 == 0) { std::cout<<"Wrong Move\n"; return;}
			j = (j-1)/2;
		}
	}
	else return;
}
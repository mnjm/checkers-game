#include"Objects.h"
#include<math.h>
#include<iostream>
bool is_rotating = false;
bool is_first_time = true;
GLint window_width,window_height,window_start_x,window_start_y;
Board board_obj;
Score_Board score_board_obj;
Pawn pawns[24];
int pawn_selected = -1;
bool is_player2_turn = false;
int board[8][8];
void init()
{
	int count = 0;
	for(int i = 1; i<8; i+=2)
		board[i][0] = -1;
	for(int i = 0; i<8; i++)
	{
		board[3][i] = -1;
		board[4][i] = -1;
	}
	for(int i = 0; i<3; i++)
	{
		for(int j = i%2; j<8; j+=2)
		{
			pawns[count].create_pawn(j,i,1);
			board[i][j] = count++;
			board[i][j+1] = -1;
		}
	}
	for(int i = 5; i<8; i++)
	{
		for(int j = i%2; j<8; j+=2)
		{
			pawns[count].create_pawn(j,i,2);
			board[i][j] = count++;
			board[i][j+1] = -1;
		}
	}
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
		glutPostRedisplay(); // Registering Display Event.

		// Calculate The Indexes
		x-= window_start_x;
		y = window_height -y; y-= window_start_y;
		int i = (int)floor(y / (77.777777777777777));
		int j = (int)floor(x / 87.5);
		if( i%2 != j%2) { score_board_obj.message("Wrong Move!"); return; } // Checking if the Shaded Cube is selected.
		if(is_player2_turn == false)
		{ // Player 1
			if( pawns[board[i][j]].player == 2) // If Player's Pawn is selected.
			{
				score_board_obj.message("Wrong Move!");
				return;
			}
			if(pawn_selected == -1) // If No pawn is selected.
			{
				if( board[i][j] == -1) // If Empty Space is selected.
				{
					score_board_obj.message("Wrong Move!");
					return;
				}
				pawn_selected = board[i][j];
				pawns[board[i][j]].is_selected = true;
			}
			if( pawns[board[i][j]].player == 1) // If player 1's pawn is selected.
			{
				pawns[pawn_selected].is_selected = false;
				pawn_selected = board[i][j];
				pawns[pawn_selected].is_selected = true;
			}
			if( ((pawns[pawn_selected].x == j-1) || (pawns[pawn_selected].x == j+1)) && pawns[pawn_selected].y == i-1) // If a place diagonally adjust is selected.
			{
				pawns[pawn_selected].is_selected = false; // Un"Select" the pawn.
				board[pawns[pawn_selected].y][pawns[pawn_selected].x] = -1; //Change the source board values to -1.
				board[i][j] = pawn_selected; // Add the destination board value.
				pawns[pawn_selected].x = j; // Change the co-ordinate of the pawn.
				pawns[pawn_selected].y = i;
				pawn_selected = -1; // Un"Select" the pawn index.
				score_board_obj.message(""); //Clear any message.
				is_player2_turn = true; //Player 2's Turn.
			}
		}
		else
		{ // Player 2
			if( pawns[board[i][j]].player == 1)
			{
				score_board_obj.message("Wrong Move!");
				return;
			}
			if(pawn_selected == -1)
			{
				if( board[i][j] == -1 )
				{
					score_board_obj.message("Wrong Move!");
					return;
				}
				pawn_selected = board[i][j];
				pawns[board[i][j]].is_selected = true;
			}
			if( pawns[board[i][j]].player == 2)
			{
				pawns[pawn_selected].is_selected = false;
				pawn_selected = board[i][j];
				pawns[pawn_selected].is_selected = true;
			}
			if( ((pawns[pawn_selected].x == j-1) || (pawns[pawn_selected].x == j+1)) && pawns[pawn_selected].y == i+1) // If a place diagonally adjust is selected.
			{
				pawns[pawn_selected].is_selected = false; // Un"Select" the pawn.
				board[pawns[pawn_selected].y][pawns[pawn_selected].x] = -1; //Change the source board values to -1.
				board[i][j] = pawn_selected; // Add the destination board value.
				pawns[pawn_selected].x = j; // Change the co-ordinate of the pawn.
				pawns[pawn_selected].y = i;
				pawn_selected = -1; // Un"Select" the pawn index.
				score_board_obj.message("Player 1's Turn"); //Clear any message and display that the chance is for player 1.
				is_player2_turn = true; //Player 1's Turn.
			}
		}
	}
}
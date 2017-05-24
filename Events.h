/*
	* This header contains the Event handlers and other functions. The checker algorithm is defined in this header in mouse event handler.
	*
	* Author: Manjunath M
	* Email: manjunath.bsk3@gmail.com
*/
#include"Objects.h"
#include<math.h>
#include<stdio.h>
bool is_rules_displayed = true;
bool popup_not_registered = true;
bool is_first_time = true;
bool is_fullscreen = false;
bool is_game_won = false;
GLint window_width,window_height,window_start_x,window_start_y;
Board board_obj;
Score_Board score_board_obj;
Pawn pawns[24];
int pawn_selected = -1;
extern bool is_player2_turn;
int board[8][8];
void popupmenu_handler(int);
void init()
{
	is_first_time = true;
	is_fullscreen = false;
	pawn_selected = -1;
	is_player2_turn = false;
	score_board_obj.reset_the_score();
	score_board_obj.message("Player 1's Turn");
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
	if( popup_not_registered )
	{
		glutCreateMenu(popupmenu_handler);
		glutAddMenuEntry("Restart Game [R/r]",3);
		glutAddMenuEntry("Exit/Quit [Q/q]",4);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
		popup_not_registered = false;
	}
}
void display_event_handler()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f,1.0f,1.0f,0.0f);
	draw_border();
	if(is_rules_displayed) 
	{
		draw_rules();
		return;
	}
	board_obj.draw();
	if(is_first_time) { init(); is_first_time = false; }
	int winner = score_board_obj.check_winner();
	if(winner == 1)
	{
		score_board_obj.draw();
		for(int i = 0; i<24; i++)
			pawns[i].draw();
		score_board_obj.message("Player 1 wins");
		glutSwapBuffers();
		return;
	}
	else if(winner == 2)
	{
		score_board_obj.draw();
		for(int i = 0; i<24; i++)
			pawns[i].draw();
		score_board_obj.message("Player 2 wins");
		glutSwapBuffers();
		return;
	}
	for(int i = 0; i<24; i++)
		pawns[i].draw();
	score_board_obj.draw();
	glutSwapBuffers(); //Swapping Back and Front Buffers.
}
void reshape_event_handler(int w,int h)
{
	if(!is_fullscreen)
	{
		window_width = w;
		window_height = h;
	}
	if( w < 700 || h < 700)
		score_board_obj.message("Don't Reduce the Window Size");
	else
	{
		window_start_x = w / 2 - 350;
		window_start_y = h / 2 - 350;
	}
	glViewport(window_start_x,window_start_y,700,700);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-41,41,-41,51);
	glMatrixMode(GL_MODELVIEW);
}
void keyboard_event_handler(unsigned char ch,int x,int y)
{
	if ( ch == 'q' || ch == 'Q' )
		exit(0);
	else if( is_rules_displayed && (ch == 's' || ch == 'S') )
	{
		is_rules_displayed = false;
		glutPostRedisplay();
	}
	else if( !is_rules_displayed && ( ch == 'r' || ch == 'R' ) )
		init();
	glutPostRedisplay();
}
void check_king_pawn(int selected_pawn)
{
	if(pawns[selected_pawn].player == 1 && pawns[selected_pawn].y == 7) // Player 1
		pawns[selected_pawn].king_pawn = true;
	else if(pawns[selected_pawn].player == 2 && pawns[selected_pawn].y == 0) // Player 2
		pawns[selected_pawn].king_pawn = true;
}
void mouse_event_handler(int button,int action,int x,int y)
{
	if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
	{
		// Calculate The Indexes
		x-= window_start_x; // If clicked out of board.
		y = window_height -y; y-= window_start_y;
		glutPostRedisplay(); // Registering Display Event.
		if( is_rules_displayed )
		{
			float i = y / 77.7777777777777f;
			float j = x / 87.5f;
			if( i > 0 && i < 0.5 && j > 0 && j < 0.8 )
				exit(0);
			else if(i > 0 && i < 0.5 && j > 7.0 && j < 8.0)
				is_rules_displayed = false;
			return;
		}
		int i = (int)floor(y / (77.777777777777777));
		int j = (int)floor(x / 87.5);

		if( i >= 8 ) return;
		if( i%2 != j%2) { score_board_obj.message("Wrong Move!"); return; } // Checking if the Shaded Cube is selected.
		if(is_player2_turn == false)
		{ 
			/*
			*============================================
			*===================Player 1=================
			*============================================
			*/
			if( pawns[board[i][j]].player == 2) // If Player 2's Pawn is selected.
			{
				score_board_obj.message("Wrong Move!");
				return;
			}
			if(pawn_selected == -1) // If No pawn is selected before.
			{
				if( board[i][j] == -1) // If Empty Space is selected.
				{
					score_board_obj.message("Wrong Move!");
					return;
				}
				pawn_selected = board[i][j];
				pawns[board[i][j]].is_selected = true;
				return;
			}
			if( pawns[board[i][j]].player == 1) // If player 1's pawn is selected.
			{
				pawns[pawn_selected].is_selected = false;
				pawn_selected = board[i][j];
				pawns[pawn_selected].is_selected = true;
				return;
			}
			if( ((pawns[pawn_selected].x == j-1) || (pawns[pawn_selected].x == j+1)) && pawns[pawn_selected].y == i-1) // If the place diagonally adjacent is selected.
			{
				pawns[pawn_selected].is_selected = false; // Un"Select" the pawn.
				board[pawns[pawn_selected].y][pawns[pawn_selected].x] = -1; //Change the source board values to -1.
				board[i][j] = pawn_selected; // Add the destination board value.
				pawns[pawn_selected].x = j; // Change the co-ordinate of the pawn.
				pawns[pawn_selected].y = i;
				check_king_pawn(pawn_selected); // Checking weather pawn is eligible for king pawn.
				pawn_selected = -1; // Un"Select" the pawn index.
				score_board_obj.message("Player 2's Turn"); //Clear any message and display that it is player 2's turn.
				is_player2_turn = true; //Player 2's Turn.
				return;
			}
			if( pawns[pawn_selected].king_pawn && ((pawns[pawn_selected].x == j-1) || (pawns[pawn_selected].x == j+1)) && pawns[pawn_selected].y == i+1) // If the place diagonally adjacent is selected.
			{
				pawns[pawn_selected].is_selected = false; // Un"Select" the pawn.
				board[pawns[pawn_selected].y][pawns[pawn_selected].x] = -1; //Change the source board values to -1.
				board[i][j] = pawn_selected; // Add the destination board value.
				pawns[pawn_selected].x = j; // Change the co-ordinate of the pawn.
				pawns[pawn_selected].y = i;
				check_king_pawn(pawn_selected); // Checking weather pawn is eligible for king pawn.
				pawn_selected = -1; // Un"Select" the pawn index.
				score_board_obj.message("Player 2's Turn"); //Clear any message and display that it is player 2's turn.
				is_player2_turn = true; //Player 2's Turn.
				return;
			}
			if( pawns[pawn_selected].y == i-2 ) // If the move is jump
			{
				if(pawns[pawn_selected].x == j-2 && pawns[board[i-1][j-1]].player == 2) //Checking for Jumping criteria towards right
				{
					pawns[board[i-1][j-1]].active = false; // Donot display the Player 2's pawn which is diagonnaly adjacent to selected pawn.
					board[i-1][j-1] = -1; // Removing that pawn from board matrix.
					score_board_obj.increment_score(1); // Incrementing the score of Player 1.
					pawns[pawn_selected].x = j; pawns[pawn_selected].y = i; // Replace the selected pawn to the 2*diagonaly adjacent to the pawn on right side.
					board[i][j] = pawn_selected; // Making changes to Board matrix
					board[i-2][j-2] = -1;
					pawns[pawn_selected].is_selected = false; // Un"selecting" the pawn
					check_king_pawn(pawn_selected); // Checking weather pawn is eligible for king pawn.
					pawn_selected = -1; // Reseting the pawn index.
					score_board_obj.message("Player 2's Turn");
					is_player2_turn = true; // Player 2's turn. ---------------------------------Perform Double or more jumps------------------
					return;
				}
				else if(pawns[pawn_selected].x == j+2 && pawns[board[i-1][j+1]].player == 2) //Checking for Jumping criteria towards left
				{
					pawns[board[i-1][j+1]].active = false; // Donot display the Player 2's pawn which is diagonnaly adjacent to selected pawn.
					board[i-1][j+1] = -1; // Removing that pawn from board matrix.
					score_board_obj.increment_score(1); // Incrementing the score of Player 1.
					pawns[pawn_selected].x = j; pawns[pawn_selected].y = i;  // Replace the selected pawn to the 2*diagonaly adjacent to the pawn on left side.
					board[i][j] = pawn_selected; // Making changes to Board matrix
					board[i-2][j+2] = -1;
					pawns[pawn_selected].is_selected = false; // Un"selecting" the pawn
					check_king_pawn(pawn_selected); // Checking weather pawn is eligible for king pawn.
					pawn_selected = -1; // Reseting the pawn index.
					score_board_obj.message("Player 2's Turn");
					is_player2_turn = true; // Player 2's turn. ---------------------------------Perform Double or more jumps------------------
					return;
				}
				else
				{
					score_board_obj.message("Wrong Move!");
					return;
				}
			}
			if( pawns[pawn_selected].king_pawn && pawns[pawn_selected].y == i+2 ) // If the move is jump
			{
				if(pawns[pawn_selected].x == j-2 && pawns[board[i+1][j-1]].player == 2) //Checking for Jumping criteria towards right
				{
					pawns[board[i+1][j-1]].active = false; // Donot display the Player 2's pawn which is diagonnaly adjacent to selected pawn.
					board[i+1][j-1] = -1; // Removing that pawn from board matrix.
					score_board_obj.increment_score(1); // Incrementing the score of Player 1.
					pawns[pawn_selected].x = j; pawns[pawn_selected].y = i; // Replace the selected pawn to the 2*diagonaly adjacent to the pawn on right side.
					board[i][j] = pawn_selected; // Making changes to Board matrix
					board[i+2][j-2] = -1;
					pawns[pawn_selected].is_selected = false; // Un"selecting" the pawn
					check_king_pawn(pawn_selected); // Checking weather pawn is eligible for king pawn.
					pawn_selected = -1; // Reseting the pawn index.
					score_board_obj.message("Player 2's Turn");
					is_player2_turn = true; // Player 2's turn. ---------------------------------Perform Double or more jumps------------------
					return;
				}
				else if(pawns[pawn_selected].x == j+2 && pawns[board[i+1][j+1]].player == 2) //Checking for Jumping criteria towards left
				{
					pawns[board[i+1][j+1]].active = false; // Donot display the Player 2's pawn which is diagonnaly adjacent to selected pawn.
					board[i+1][j+1] = -1; // Removing that pawn from board matrix.
					score_board_obj.increment_score(1); // Incrementing the score of Player 1.
					pawns[pawn_selected].x = j; pawns[pawn_selected].y = i;  // Replace the selected pawn to the 2*diagonaly adjacent to the pawn on left side.
					board[i][j] = pawn_selected; // Making changes to Board matrix
					board[i+2][j+2] = -1;
					pawns[pawn_selected].is_selected = false; // Un"selecting" the pawn
					check_king_pawn(pawn_selected); // Checking weather pawn is eligible for king pawn.
					pawn_selected = -1; // Reseting the pawn index.
					score_board_obj.message("Player 2's Turn");
					is_player2_turn = true; // Player 2's turn. ---------------------------------Perform Double or more jumps------------------
					return;
				}
				else
				{
					score_board_obj.message("Wrong Move!");
					return;
				}
			}
		}
		else
		{ 
			/*
			*===============================================
			*===================Player 2====================
			*===============================================
			*/
			if( pawns[board[i][j]].player == 1) // If Player 1's Pawn is selected.
			{
				score_board_obj.message("Wrong Move!");
				return;
			}
			if(pawn_selected == -1) // If No pawn is selected before.
			{
				if( board[i][j] == -1 ) // If Empty Space is selected.
				{
					score_board_obj.message("Wrong Move!");
					return;
				}
				pawn_selected = board[i][j];
				pawns[board[i][j]].is_selected = true;
				return;
			}
			if( pawns[board[i][j]].player == 2) // If player 2's pawn is selected.
			{
				pawns[pawn_selected].is_selected = false;
				pawn_selected = board[i][j];
				pawns[pawn_selected].is_selected = true;
				return;
			}
			if( ((pawns[pawn_selected].x == j-1) || (pawns[pawn_selected].x == j+1)) && pawns[pawn_selected].y == i+1) // If a place diagonally adjust is selected.
			{
				pawns[pawn_selected].is_selected = false; // Un"Select" the pawn.
				board[pawns[pawn_selected].y][pawns[pawn_selected].x] = -1; //Change the source board values to -1.
				board[i][j] = pawn_selected; // Add the destination board value.
				pawns[pawn_selected].x = j; // Change the co-ordinate of the pawn.
				pawns[pawn_selected].y = i;
				check_king_pawn(pawn_selected); // Checking weather pawn is eligible for king pawn.
				pawn_selected = -1; // Un"Select" the pawn index.
				score_board_obj.message("Player 1's Turn"); //Clear any message and display that the chance is for player 1.
				is_player2_turn = false; //Player 1's Turn.
				return;
			}
			if(pawns[pawn_selected].king_pawn && ((pawns[pawn_selected].x == j-1) || (pawns[pawn_selected].x == j+1)) && pawns[pawn_selected].y == i-1) // If a place diagonally adjust is selected.
			{
				pawns[pawn_selected].is_selected = false; // Un"Select" the pawn.
				board[pawns[pawn_selected].y][pawns[pawn_selected].x] = -1; //Change the source board values to -1.
				board[i][j] = pawn_selected; // Add the destination board value.
				pawns[pawn_selected].x = j; // Change the co-ordinate of the pawn.
				pawns[pawn_selected].y = i;
				check_king_pawn(pawn_selected); // Checking weather pawn is eligible for king pawn.
				pawn_selected = -1; // Un"Select" the pawn index.
				score_board_obj.message("Player 1's Turn"); //Clear any message and display that the chance is for player 1.
				is_player2_turn = false; //Player 1's Turn.
				return;
			}
			if( pawns[pawn_selected].y == i+2 ) // If the move is jump
			{
				if(pawns[pawn_selected].x == j-2 && pawns[board[i+1][j-1]].player == 1) //Checking for Jumping criteria towards right
				{
					pawns[board[i+1][j-1]].active = false; // Donot display the Player 1's pawn which is diagonnaly adjacent to selected pawn.
					board[i+1][j-1] = -1; // Removing that pawn from board matrix.
					score_board_obj.increment_score(2); // Incrementing the score of Player 2.
					pawns[pawn_selected].x = j; pawns[pawn_selected].y = i; // Replace the selected pawn to the 2*diagonaly adjacent to the pawn on right side.
					board[i][j] = pawn_selected; // Making changes to Board matrix
					board[i+2][j-2] = -1;
					pawns[pawn_selected].is_selected = false; // Un"selecting" the pawn
					check_king_pawn(pawn_selected); // Checking weather pawn is eligible for king pawn.
					pawn_selected = -1; // Reseting the pawn index.
					score_board_obj.message("Player 1's Turn");
					is_player2_turn = false; // Player 1's turn. ---------------------------------Perform Double or more jumps------------------
					return;
				}
				else if(pawns[pawn_selected].x == j+2 && pawns[board[i+1][j+1]].player == 1) //Checking for Jumping criteria towards left
				{
					pawns[board[i+1][j+1]].active = false; // Donot display the Player 1's pawn which is diagonnaly adjacent to selected pawn.
					board[i+1][j+1] = -1; // Removing that pawn from board matrix.
					board[i+2][j+2] = -1; // Making chan
					score_board_obj.increment_score(2); // Incrementing the score of Player 2.
					pawns[pawn_selected].x = j; pawns[pawn_selected].y = i;  // Replace the selected pawn to the 2*diagonaly adjacent to the pawn on left side.
					board[i][j] = pawn_selected; // Making changes to Board matrix
					board[i+2][j-1] = -1;
					pawns[pawn_selected].is_selected = false; // Un"selecting" the pawn
					check_king_pawn(pawn_selected); // Checking weather pawn is eligible for king pawn.
					pawn_selected = -1; // Reseting the pawn index.
					score_board_obj.message("Player 1's Turn");
					is_player2_turn = false; // Player 1's turn. ---------------------------------Perform Double or more jumps------------------
					return;
				}
				else
				{
					score_board_obj.message("Wrong Move!");
					return;
				}
			}
			if( pawns[pawn_selected].king_pawn && pawns[pawn_selected].y == i-2 ) // If the move is jump
			{
				if(pawns[pawn_selected].x == j-2 && pawns[board[i-1][j-1]].player == 1) //Checking for Jumping criteria towards right
				{
					pawns[board[i-1][j-1]].active = false; // Donot display the Player 1's pawn which is diagonnaly adjacent to selected pawn.
					board[i-1][j-1] = -1; // Removing that pawn from board matrix.
					score_board_obj.increment_score(2); // Incrementing the score of Player 2.
					pawns[pawn_selected].x = j; pawns[pawn_selected].y = i; // Replace the selected pawn to the 2*diagonaly adjacent to the pawn on right side.
					board[i][j] = pawn_selected; // Making changes to Board matrix
					board[i-2][j-2] = -1;
					pawns[pawn_selected].is_selected = false; // Un"selecting" the pawn
					check_king_pawn(pawn_selected); // Checking weather pawn is eligible for king pawn.
					pawn_selected = -1; // Reseting the pawn index.
					score_board_obj.message("Player 1's Turn");
					is_player2_turn = false; // Player 1's turn. ---------------------------------Perform Double or more jumps------------------
					return;
				}
				else if(pawns[pawn_selected].x == j+2 && pawns[board[i-1][j+1]].player == 1) //Checking for Jumping criteria towards left
				{
					pawns[board[i-1][j+1]].active = false; // Donot display the Player 1's pawn which is diagonnaly adjacent to selected pawn.
					board[i-1][j+1] = -1; // Removing that pawn from board matrix.
					score_board_obj.increment_score(2); // Incrementing the score of Player 2.
					pawns[pawn_selected].x = j; pawns[pawn_selected].y = i;  // Replace the selected pawn to the 2*diagonaly adjacent to the pawn on left side.
					board[i][j] = pawn_selected; // Making changes to Board matrix
					board[i-2][j-1] = -1;
					pawns[pawn_selected].is_selected = false; // Un"selecting" the pawn
					check_king_pawn(pawn_selected); // Checking weather pawn is eligible for king pawn.
					pawn_selected = -1; // Reseting the pawn index.
					score_board_obj.message("Player 1's Turn");
					is_player2_turn = false; // Player 1's turn. ---------------------------------Perform Double or more jumps------------------
					return;
				}
				else
				{
					score_board_obj.message("Wrong Move!");
					return;
				}
			}
		}
	}
}
void popupmenu_handler(int id)
{
	if(id == 3) // Restart the Game.
		init();
	else if(id == 4) // Quit from the game.
		exit(0);
	glutPostRedisplay();
}
#include<GL/glut.h>
#include<math.h>
#define TWO_PI 6.28571428f
class Board
{
public:
	Board() {}
	virtual ~Board() {}
	void draw()
	{
		int color = 0;
		GLfloat x,y;
		for(int i = 0; i < 8; i++ )
		{
			color = i % 2 ;
			for(int j = 0; j < 8; j++)
			{
				glBegin(GL_QUADS);
				if(color == 0) { glColor3f(1.0f,0.0f,0.0f);/* Red Color */ color = 1; }
				else { glColor3f(0.0f,1.0f,0.0f);  /* Green Color */ color = 0; }
				x = -40.0f + ( i * 10);
				y = -40.0f + ( j * 10);
				glVertex2f(x, y);
				glVertex2f(x+10, y);
				glVertex2f(x+10, y+10);
				glVertex2f(x, y+10);
				glEnd();
			}
		}

	}
};
class Pawn
{
public:
	int x,y,player;
	bool is_selected;
	bool active;
	bool king_pawn;
	Pawn() {
		is_selected = false;
		active = true;
		king_pawn = false;
	}
	void create_pawn(int _x,int _y,int _player)
	{
		x = _x; y = _y; player = _player;
	}
	int which_player()
	{
		return player;
	}
	void draw()
	{
		if(!active) return;
		GLfloat center_x,center_y;
		if ( player == 1 ) glColor3f(1.0f,1.0f,1.0f); // Player 1 Pawn Color
		else glColor3f(0.0f,0.0f,0.0f); // Player 2 Pawn Color
		center_y = -35.0f /* -40 + 5 */ + (GLfloat)(y*10);
		if( y%2 == 0) center_x = -35.0f /* -40 + 5 */ + (GLfloat)(x*20);
		else center_x = -25.0f /* -40 + 5 */ + (GLfloat)(x*20);
		glBegin(GL_POLYGON);
		for(float theta = 0.0; theta <  TWO_PI; theta += 0.2f)
			glVertex2f(center_x + 4.5f * cos(theta), center_y + 4.5f * sin(theta));
		glEnd();
		if(is_selected)
		{
			if(player == 1) glColor3f(0.0f,0.0f,0.0f);
			else glColor3f(1.0f,1.0f,1.0f);
			glLineWidth(2);
			glBegin(GL_LINE_LOOP);
			for(float theta = 0.0; theta <  TWO_PI; theta += 0.5f )
				glVertex2f(center_x + 4.9f * cos(theta), center_y + 4.9f * sin(theta));
			glEnd();
		}
		if(king_pawn)
		{
			if(player == 1) glColor3f(0.0f,0.0f,0.0f);
			else glColor3f(1.0f,1.0f,1.0f);
			glBegin(GL_LINE_STRIP);
			for(float theta = 0.0,count = 0; count < 6; theta += 2.51428f,count++)
				glVertex2f(center_x + 4.5f * cos(theta), center_y + 4.5f * sin(theta));
			glEnd();
		}
	}
};
class Score_Board
{
public:
	
};
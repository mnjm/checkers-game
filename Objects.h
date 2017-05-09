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
private:
	int x,y,player;
	bool is_selected;
	bool active;
public:
	Pawn() {
		is_selected = false;
		active = true;
	}
	void create_pawn(int _x,int _y,int _player)
	{
		x = _x; y = _y; player = _player;
	}
	int which_player()
	{
		return player;
	}
	void get_the_index(int *_x,int *_y)
	{
		*_x = x; *_y = y; return;
	}
	void set_is_selected(bool val)
	{
		is_selected = val;
	}
	bool set_is_selected()
	{
		return is_selected;
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
			glPointSize(2);
			glBegin(GL_POINTS);
			for(float theta = 0.0; theta <  TWO_PI; theta += 0.02f)
				glVertex2f(center_x + 4.9f * cos(theta), center_y + 4.9f * sin(theta));
			glEnd();
		}
	}
};
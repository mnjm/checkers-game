#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
GLfloat cos_vals[] = {1.0f,0.980067f,0.921061f,0.825336f,0.696707f,0.540302f,0.362358f,0.169967f,-0.0291997f,-0.227202f,-0.416147f,-0.588501f,-0.737394f,-0.856889f,-0.942222f,-0.989993f,-0.998295f,-0.966798f,-0.896758f,-0.790967f,-0.653643f,-0.490261f,-0.307333f,-0.112153f,0.0874987f,0.283662f,0.468516f,0.634692f,0.775565f,0.885519f,0.96017f,0.996542f};
GLfloat sin_vals[] = {0.0f,0.198669f,0.389418f,0.564642f,0.717356f,0.841471f,0.932039f,0.98545f,0.999574f,0.973848f,0.909297f,0.808496f,0.675463f,0.515501f,0.334988f,0.14112f,-0.0583747f,-0.255542f,-0.442521f,-0.611858f,-0.756803f,-0.871576f,-0.951602f,-0.993691f,-0.996165f,-0.958924f,-0.883455f,-0.772765f,-0.631267f,-0.464603f,-0.279417f,-0.083091f};

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
				if(color == 0) { glColor3f(1.0f,1.0f,1.0f); color = 1; }
				else { glColor3f(0.403921f,0.403921f,0.403921f); color = 0; }
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
	void draw_circle(GLfloat x,GLfloat y,GLfloat radius)
	{
		for(int i = 0; i < 32; i++ )
			glVertex2f(x + radius * cos_vals[i], y + radius * sin_vals[i]);
	}
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
		active = true;
		is_selected = false;
		king_pawn = false;
	}
	int which_player()
	{
		return player;
	}
	void draw()
	{
		if(!active) return;
		GLfloat center_x,center_y;
		if ( player == 1 ) glColor3f(1.0f,0.5725f,0.14117f); // Player 1 Pawn Color
		else glColor3f(0.0f,0.88235f,0.88235f); // Player 2 Pawn Color
		center_x = -35.0f + x*10;
		center_y = -35.0f + y*10;
		glBegin(GL_POLYGON);
		draw_circle(center_x,center_y,4.5f);
		glEnd();
		if ( player == 1) glColor3f(0.35686f,0.1804f,0.0f);
		else glColor3f(0.0f,0.25098f,0.25098f);
		glBegin(GL_LINE_LOOP);
		draw_circle(center_x,center_y,4.6f);
		glEnd();
		if(is_selected)
		{
			glColor3f(0.0f,0.0f,0.0f);
			glLineWidth(2);
			glBegin(GL_LINE_LOOP);
			draw_circle(center_x,center_y,4.9f);
			glEnd();
		}
		if(king_pawn)
		{
			glColor3f(1.0f,1.0f,0.0f);
			glBegin(GL_TRIANGLES);
			glVertex2f(center_x + 3.5f * cos(0.7854f), center_y + 3.5f * sin(0.7854f));
			glVertex2f(center_x + 3.0f * cos(3.9270f), center_y + 3.0f * sin(3.9270f));
			glVertex2f(center_x + 3.0f * cos(5.4972f), center_y + 3.0f * sin(5.4978f));

			glVertex2f(center_x + 3.5f * cos(2.3562f), center_y + 3.5f * sin(2.3562f));
			glVertex2f(center_x + 3.0f * cos(3.9270f), center_y + 3.0f * sin(3.9270f));
			glVertex2f(center_x + 3.0f * cos(5.4972f), center_y + 3.0f * sin(5.4978f));

			glVertex2f(center_x + 2.0f * cos(1.1781f), center_y + 2.0f * sin(1.1781f));
			glVertex2f(center_x + 3.5f * cos(1.5708f), center_y + 3.5f * sin(1.5708f));
			glVertex2f(center_x + 2.0f * cos(1.9635f), center_y + 2.0f * sin(1.9635f));
			glEnd();
		}
	}
};
class Score_Board
{
private: 
	unsigned int temp; // Check this.
	unsigned int p1_score;
	unsigned int p2_score;
	char msg[100];
	void type(const char *str,double x,double y,double sx,double sy)
	{
		glPushMatrix();
		glTranslated(x,y,0.0);
		glScaled(sx,sy,0.0);
		glLineWidth(3.0f);
		while(*str != NULL)
		{
			glutStrokeCharacter(GLUT_STROKE_ROMAN, (int) *str);
			str++;
		}
		glPopMatrix();
	}
public:
	Score_Board()
	{
		p1_score = p2_score = 0;
		sprintf_s(msg,"Player 1's Turn");
	}
	void increment_score(int player)
	{
		if(player == 1) p1_score++;
		else if(player == 2) p2_score++;
	}
	int check_winner()
	{
		if(p1_score == 12)
			return 1;
		else if(p2_score == 12)
			return 2;
		else return -1;
	}
	void reset_the_score()
	{
		p1_score = p2_score = 0;
	}
	void message(const char *_msg)
	{
		sprintf_s(msg,"%s",_msg);
	}
	void draw()
	{
		// Player 1
		glColor3f(0.2f,0.2f,0.2f);
		glBegin(GL_QUADS);
		glVertex2f(-40.0f,+40.0f); glVertex2f(-20.0f,+40.0f);
		glVertex2f(-20.0f,+50.0f); glVertex2f(-40.0f,+50.0f);
		glEnd();
		glColor3d(1.0,1.0,1.0);
		type("Player 1",-39.0,+47.0,0.025,0.025);
		char buff[30];
		sprintf_s(buff,"Score: %d",p1_score);
		type(buff,-39.0,+43.0,0.022,0.022);

		// Player 2
		glColor3f(0.2f,0.2f,0.2f);
		glBegin(GL_QUADS);
		glVertex2f(+20.0f,+40.0f); glVertex2f(+40.0f,+40.0f);
		glVertex2f(+40.0f,+50.0f); glVertex2f(+20.0f,+50.0f);
		glEnd();
		glColor3d(1.0,1.0,1.0);
		type("Player 2",21.0,+47.0,0.025,0.025);
		sprintf_s(buff,"Score: %d",p2_score);
		type(buff,21.0,+43.0,0.022,0.022);

		//Message
		type(msg,-14.0,+44.0,0.03,0.03);
	}
};
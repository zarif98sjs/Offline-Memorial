#include "iGraphics.h"
#include<time.h>
#define pi 3.14159

double rad(double deg)
{
    return ((deg*pi)/180.0);
}

int x = 300, y = 300, r = 210;
double rh=130,rm=170,rs=190;
double h,m,s,h_ang,m_ang,s_ang,hx,hy,mx,my,sx,sy;

double h0x = rh*sin(rad(90)), h0y=rh*cos(rad(90));
double m0x = rm*sin(rad(90)), m0y=rm*cos(rad(90));
double s0x = rs*sin(rad(90)), s0y=rs*cos(rad(90));

void ghurano()
{
    hx=rh*sin(rad(h_ang+(30.0/3600.0)));
    hy=rh*cos(rad(h_ang+(30.0/3600.0)));
    h_ang+=(30.0/3600.0);

    mx=rm*sin(rad(m_ang+(6.0/60.0)));
    my=rm*cos(rad(m_ang+(6.0/60.0)));
    m_ang+=(6.0/60.0);
    sx=rs*sin(rad(s_ang+6.0));
    sy=rs*cos(rad(s_ang+6.0));
    s_ang+=(6.0);
}


void iDraw()
{
    //place your drawing codes here
    iClear();
    iSetColor(66, 212, 244);
    iFilledCircle(x, y, r);
    iSetColor(20, 10, 10);
    iFilledCircle(x,y,5);

    iLine(x,y,x+hx,y+hy);
    iLine(x,y,x+mx,y+my);
    iLine(x,y,x+sx,y+sy);

    //iFilledRectangle(10, 30, 20, 20);
    iSetColor(20, 200, 0);

    for(int i=0,j=12; i<=11; i++,j++)
    {
        if(j>12)
            j=j%12;

        char str[10];
        sprintf(str, "%d", j);

        iSetColor(40,40,40);
        iText(x+rs*sin(rad(i*30)),y+rs*cos(rad(i*30)),str,GLUT_BITMAP_9_BY_15);
    }

    iSetColor(50,250,50);
    iText(40, 40, "CLOCK");
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    printf("x = %d, y= %d\n",mx,my);
    //place your codes here
}


/*
    function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    /*if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        //	printf("x = %d, y= %d\n",mx,my);
        x += 10;
        y += 10;
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        x -= 10;
        y -= 10;
    }*/
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key)
{
    if (key == 'q')
    {
        exit(0);
    }
    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key)
{

    if (key == GLUT_KEY_END)
    {
        exit(0);
    }
    //place your codes for other keys here
}


int main()
{

    //time_t t;
    //time(&t);
    //clrscr();

    //printf("Today's date and time : %s",ctime(&t));
    //getch();

    //struct tm *tm_struct = localtime(time(NULL));

    /*h = localtime(time(NULL))->tm_hour;
    m = localtime(time(NULL))->tm_min;
    s = localtime(time(NULL))->tm_sec;
    */

    time_t now;
    struct tm *now_tm;
    int hour;

    now = time(NULL);
    now_tm = localtime(&now);
    h = now_tm->tm_hour;
    m = now_tm->tm_min;
    s = now_tm->tm_sec;


    //scanf("%lf %lf %lf",&h,&m,&s);

    h_ang=h*30+m*.5+(s*30)/3600.0;
    m_ang=m*6+(s*6)/60.0;
    s_ang=s*6;

    hx=rh*sin(rad(h_ang));
    hy=rh*cos(rad(h_ang));

    mx=rm*sin(rad(m_ang));
    my=rm*cos(rad(m_ang));

    sx=rs*sin(rad(s_ang));
    sy=rs*cos(rad(s_ang));


    iSetTimer(1000,ghurano);

    //place your own initialization codes here.
    iInitialize(600, 600, "demo");
    return 0;
}

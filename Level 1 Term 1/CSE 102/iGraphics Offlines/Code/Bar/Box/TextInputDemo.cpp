# include "iGraphics.h"

char str[100], str2[100];
int len;
int mode;
int siz;

double r=120,g=50,b=150;


void drawTextBox()
{
    iSetColor(150, 150, 150);
    iRectangle(50, 250, 250, 30);
}

//int ara[20][10];

int ara0[]={0,1,1,1,1,1,1,0};
int ara1[]={0,0,1,1,0,0,0,0};
int ara2[]={0,1,1,0,1,1,0,1};
int ara3[]={0,1,1,1,1,0,0,1};
int ara4[]={0,0,1,1,0,0,1,1};
int ara5[]={0,1,0,1,1,0,1,1};
int ara6[]={0,1,0,1,1,1,1,1};
int ara7[]={0,1,1,1,0,0,0,0};
int ara8[]={0,1,1,1,1,1,1,1};
int ara9[]={0,1,1,1,1,0,1,1};
int araA[]={0,1,1,1,0,1,1,1};
int arab[]={0,0,0,1,1,1,1,1};
int araC[]={0,1,0,0,1,1,1,0};
int araD[]={0,1,1,1,1,1,1,0};
int araE[]={0,1,0,0,1,1,1,1};
int araF[]={0,1,0,0,0,1,1,1};

int x=100,y=80,z=60;

void buildSegment(int ara[],int f)//factor
{
    for(int i=1; i<=7; i++)
    {
        if(i==1 && ara[i]==1)
            iFilledRectangle(x+f,y+70,50,10);
       if(i==2 &&ara[i]==1)
            iFilledRectangle(x+40+f,y+35,10,45);
        if(i==3 &&ara[i]==1)
            iFilledRectangle(x+40+f,y,10,45);
        if(i==4 &&ara[i]==1)
            iFilledRectangle(x+f,y,50,10);
        if(i==5 &&ara[i]==1)
            iFilledRectangle(x+f,y,10,45);
        if(i==6 &&ara[i]==1)
            iFilledRectangle(x+f,y+35,10,45);
        if(i==7 &&ara[i]==1)
            iFilledRectangle(x+f,y+35,50,10);

    }

}


void dekhano()
{
    siz=strlen(str2);

    for(int i=0;i<strlen(str2);i++)
    {
        if(str2[i]=='0')
            buildSegment(ara0,z*i);
        if(str2[i]=='1')
            buildSegment(ara1,z*i);
        if(str2[i]=='2')
            buildSegment(ara2,z*i);
        if(str2[i]=='3')
            buildSegment(ara3,z*i);
        if(str2[i]=='4')
            buildSegment(ara4,z*i);
        if(str2[i]=='5')
            buildSegment(ara5,z*i);
        if(str2[i]=='6')
            buildSegment(ara6,z*i);
        if(str2[i]=='7')
            buildSegment(ara7,z*i);
        if(str2[i]=='8')
            buildSegment(ara8,z*i);
        if(str2[i]=='9')
            buildSegment(ara9,z*i);
        if(str2[i]=='A')
            buildSegment(araA,z*i);
        if(str2[i]=='b')
            buildSegment(arab,z*i);
        if(str2[i]=='C')
            buildSegment(araC,z*i);
        if(str2[i]=='D')
            buildSegment(araD,z*i);
        if(str2[i]=='E')
            buildSegment(araE,z*i);
        if(str2[i]=='F')
            buildSegment(araF,z*i);
    }
}

void cholbe()
{
    x=x-5;
    if(x+z*siz<0)
        x=400;
}


/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
    //place your drawing codes here

    iClear();

    drawTextBox();
    if(mode == 1)
    {
        iSetColor(255, 255, 255);
        iText(55, 260, str);
    }

    r=r+2.0;g=g+0.5,b=b+.25;
    if(r>256)
        r=0;
    if(g>256)
        g=0;
    if(b>256)
        b=0;

    iSetColor(r, g, b);
    dekhano();
    //cholbe();

    //buildSegment(ara0);
    //buildSegment(ara1);
    //buildSegment(ara2);
    //buildSegment(ara3);
    //buildSegment(ara4);
    //buildSegment(ara5);
    //buildSegment(ara6);
    //buildSegment(ara7);
    //buildSegment(ara8);
    //buildSegment(ara9);

    iText(10, 10, "Click to activate the box, enter to finish.");
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        if(mx >= 50 && mx <= 300 && my >= 250 && my <= 280 && mode == 0)
        {
            mode = 1;
        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    int i;
    if(mode == 1)
    {
        if(key == '\r')
        {
            mode = 0;
            strcpy(str2, str);
            printf("%s\n", str2);
            for(i = 0; i < len; i++)
                str[i] = 0;
            len = 0;
        }
        else
        {
            str[len] = key;
            len++;
        }
    }

    if(key == 'x')
    {
        //do something with 'x'
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

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }

    //place your codes for other keys here
}

int main()
{
    //place your own initialization codes here.
    len = 0;
    mode = 0;
    str[0]= 0;
    printf("%d\n",z*strlen(str));
    iSetTimer(60,cholbe);
    iInitialize(400, 400, "TextInputDemo");

    return 0;
}

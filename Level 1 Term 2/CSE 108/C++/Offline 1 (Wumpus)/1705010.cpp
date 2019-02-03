#include <iostream>
#include <cmath>
#include<ctime>
#include <sstream>
#include<fstream>
#include<windows.h>

using namespace std;

#define GRIDSIZE 4
#define UP      0
#define DOWN    2
#define LEFT    3
#define RIGHT   1
#define MAX_SHOTS 3


string to_stringg(int x)
{
    std::string out_string;
    std::stringstream ss;
    ss << x;
    return ss.str();
}


class Position
{

    int x, y;

public:

    Position (int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    Position() {}

    // Modify the following four so that the resulting position does not leave the grid
    void moveRight()
    {
        if(x==GRIDSIZE-1)
            cout<<"INVALID MOVE. CAN NOT MOVE TO THE RIGHT"<<endl;
        else
            x++;
    }

    void moveLeft()
    {
        if(x==0)
            cout<<"INVALID MOVE. CAN NOT MOVE TO THE LEFT"<<endl;
        else
            x--;
    }

    void moveUp()
    {
        if(y==GRIDSIZE-1)
            cout<<"INVALID MOVE. CAN NOT MOVE UP"<<endl;
        else
            y++;
    }

    void moveDown()
    {
        if(y==0)
            cout<<"INVALID MOVE. CAN NOT MOVE DOWN"<<endl;
        else
            y--;
    }

    bool isAdjacent(Position p)
    {
        //implement the function
        if(abs(x-p.getX())+abs(y-p.getY())==1)
            return true;
        return false;
    }

    bool isSamePoint(Position p)
    {
        //implement the function
        if(abs(x-p.getX())+abs(y-p.getY())==0)
            return true;
        return false;
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

};

class Wumpus
{
    bool killed;
    Position p;

public:

    Wumpus(int x, int y)
    {
        p = Position(x, y);
        killed = false;
    }

    Wumpus()
    {
        p=Position(rand()%(GRIDSIZE-1)+1,rand()%(GRIDSIZE-1)+1);
        killed=false;
        //...
    }

    void kill()
    {
        killed = true;
    }

    Position getPosition()
    {
        return p;
    }

    bool isKilled() { return killed; }
};

class Pit
{
    Position p;

public:

    Pit(int x, int y)
    {
        p = Position(x, y);
    }

    Pit()
    {
        p=Position(rand()%(GRIDSIZE-1)+1,rand()%(GRIDSIZE-1)+1);
    }

    Position getPosition()
    {
        return p;
    }
};

class Player
{
    int direction;
    int total_shots;
    bool killed;
    Position p;

public:

    Player()
    {
        direction=UP;
        total_shots=MAX_SHOTS;
        killed=false;
        p=Position(0,0);
        //...
    }

    void turnLeft()
    {
        direction=(direction+LEFT)%GRIDSIZE;
        //...
    }

    void turnRight()
    {
        direction=(direction+RIGHT)%GRIDSIZE;
        //...
    }

    void moveForward()
    {
        if(direction==UP)
            p.moveUp();
        else if(direction==RIGHT)
            p.moveRight();
        else if(direction==DOWN)
            p.moveDown();
        else if(direction==LEFT)
            p.moveLeft();
        //...
    }

    bool isAdjacent(Position pos)
    {
        return p.isAdjacent(pos);
    }

    bool isSamePoint(Position pos)
    {
        return p.isSamePoint(pos);
    }

    void kill()
    {
        killed = true;
    }

    string getPositionInfo()
    {
        return ("Player is now at " + to_stringg(p.getX()) + ", " + to_stringg(p.getY()));
        //return "Player is now at ";
    }

    string getDirectionInfo()
    {
        string s;
        if (direction == UP)
            s = "up";
        if (direction == DOWN)
            s = "down";
        if (direction == LEFT)
            s = "left";
        if (direction == RIGHT)
            s = "right";
        return "Player is moving at direction: " + s;
    }

    int get_total_shots()
    {
        return total_shots;
    }

    void set_total_shots(int val)
    {
        total_shots=val;
    }

    int get_direction()
    {
        return direction;
    }

    Position get_position()
    {
        return p;
    }
};

class WumpusWorld
{

private:

    Player player;
    Wumpus wumpus;
    Pit pit;
    Position gold_position;
    bool ended;

public:

    WumpusWorld()
    {
        //wumpus.p=Position(rand()%GRIDSIZE,rand()%GRIDSIZE);
        wumpus=Wumpus();
        gold_position=Position(rand()%(GRIDSIZE-1)+1,rand()%(GRIDSIZE-1)+1);
        pit=Pit();
        ended=false;
    }

    WumpusWorld(int wumpus_x, int wumpus_y)
    {
        //...
        //wumpus.p=Position(wumpus_x,wumpus_y);
        wumpus=Wumpus(wumpus_x,wumpus_y);
        gold_position=Position(rand()%(GRIDSIZE-1)+1,rand()%(GRIDSIZE-1)+1);
        pit=Pit();
        //pit kora lagbe
        ended=false;
    }

    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y)
    {
        //...
        //wumpus.p=Position(wumpus_x,wumpus_y);
        wumpus=Wumpus(wumpus_x,wumpus_y);
        gold_position=Position(gold_x,gold_y);
        pit=Pit();
        //pit kora lagbe
        ended=false;
    }

    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y, int pit_x, int pit_y)
    {
        //...
        //wumpus.p=Position(wumpus_x,wumpus_y);
        wumpus=Wumpus(wumpus_x,wumpus_y);
        gold_position=Position(gold_x,gold_y);
        pit=Pit(pit_x,pit_y);
        //pit
        ended=false;
    }

    void moveForward()
    {
        player.moveForward();
        return showGameState();
    }

    void turnLeft()
    {
        player.turnLeft();
        return showGameState();
    }

    void turnRight()
    {
        player.turnRight();
        return showGameState();
    }

    void shoot()
    {
        //...
        if(player.get_total_shots())
        {
            player.set_total_shots(player.get_total_shots()-1);

            if(player.get_direction()==UP)
            {
                int ix=player.get_position().getX();

                for(int iy=player.get_position().getY(); iy<GRIDSIZE; iy++)
                {
                    if(wumpus.getPosition().isSamePoint(Position(ix,iy)) && wumpus.isKilled()==true)
                        {cout<<"THIS WUMPUS IS ALREADY DEAD"<<endl;break;}
                    else if(wumpus.getPosition().isSamePoint(Position(ix,iy)) && wumpus.isKilled()==false)
                        {wumpus.kill(); wumpus.kill(); cout<<"WUMPUS IS DEAD"<<endl; break;}
                }
            }

            else if(player.get_direction()==DOWN)
            {
                int ix=player.get_position().getX();

                for(int iy=player.get_position().getY(); iy>=0; iy--)
                {
                    if(wumpus.getPosition().isSamePoint(Position(ix,iy)) && wumpus.isKilled()==true)
                        {cout<<"THIS WUMPUS IS ALREADY DEAD"<<endl;break;}
                    else if(wumpus.getPosition().isSamePoint(Position(ix,iy)) && wumpus.isKilled()==false)
                        {wumpus.kill(); wumpus.kill(); cout<<"WUMPUS IS DEAD"<<endl; break;}

                }
            }

            else if(player.get_direction()==RIGHT)
            {
                int iy=player.get_position().getY();

                for(int ix=player.get_position().getX(); ix<GRIDSIZE; ix++)
                {
                    if(wumpus.getPosition().isSamePoint(Position(ix,iy)) && wumpus.isKilled()==true)
                        {cout<<"THIS WUMPUS IS ALREADY DEAD"<<endl;break;}
                    else if(wumpus.getPosition().isSamePoint(Position(ix,iy)) && wumpus.isKilled()==false)
                        {wumpus.kill(); wumpus.kill(); cout<<"WUMPUS IS DEAD"<<endl; break;}

                }
            }

            else if(player.get_direction()==LEFT)
            {
                int iy=player.get_position().getY();

                for(int ix=player.get_position().getX(); ix>=0; ix--)
                {
                    if(wumpus.getPosition().isSamePoint(Position(ix,iy)) && wumpus.isKilled()==true)
                        {cout<<"THIS WUMPUS IS ALREADY DEAD"<<endl;break;}
                    else if(wumpus.getPosition().isSamePoint(Position(ix,iy)) && wumpus.isKilled()==false)
                        {wumpus.kill(); wumpus.kill(); cout<<"WUMPUS IS DEAD"<<endl; break;}

                }
            }

            if(wumpus.isKilled()==false)
                cout<<"MISSED SHOT"<<endl;
            else if(wumpus.isKilled()==true)
                cout<<"YOU DON'T HAVE MORE WUMPUS TO KILL"<<endl;
        }

        else
        {
            cout<<"YOU HAVE NO SHOTS LEFT"<<endl;
        }


    }

    void showGameState()
    {
        cout << endl;
        cout << player.getPositionInfo() << endl;
        cout << player.getDirectionInfo() << endl;
//        cout <<"Wumpus "<<wumpus.getPosition().getX()<<"," <<wumpus.getPosition().getY()<< endl;
//        cout <<"Pit "<<pit.getPosition().getX()<<"," <<pit.getPosition().getY()<< endl;

        if (player.isSamePoint(wumpus.getPosition()) && wumpus.isKilled()==false)
        {
            cout << "Player is killed!" << endl;
            player.kill();
            cout << "Game over!" << endl;
            Sleep(3000);
            ended = true;
        }

        else if (player.isSamePoint(pit.getPosition()))
        {
            cout << "Rot Forever!" << endl;
            player.kill();
            cout << "Game over!" << endl;
            Sleep(3000);
            ended = true;
        }

        else if (player.isSamePoint(gold_position))
        {
            cout << "Got the gold!" << endl;
            cout << "Game ended, you won!" << endl;
            Sleep(3000);
            ended = true;
        }

        else if (player.isAdjacent(wumpus.getPosition()) && wumpus.isKilled()==false)
        {
            cout << "stench!" << endl;
        }

        else if (player.isAdjacent(pit.getPosition()))
        {
            cout << "breeze!" << endl;
        }
    }

    bool isOver()
    {
        return ended;
    }

};

int main()
{
    srand((time(NULL)));

    int c, wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y;
    WumpusWorld w;

    // take the six integers input from file

    fstream myfile;
    myfile.open("input.txt", std::ios_base::in);

    if(myfile)
    {
        cout<<"GAME IS RUNNING USING THE FILE INPUTS"<<endl;
        myfile>>wumpus_x>>wumpus_y>>gold_x>>gold_y>>pit_x>>pit_y;
//        cout<<wumpus_x<<wumpus_y<<gold_x<<gold_y<<pit_x<<pit_y;
        w=WumpusWorld(wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y);
    }
    else
    {
        cout<<"NO FILE , GAME IS RUNNING ON RANDOM VALUES"<<endl;
        w=WumpusWorld();
    }

    w.showGameState();
    while (!w.isOver())
    {
        cout << "1: move forward" << endl;
        cout << "2: Turn left" << endl;
        cout << "3: Turn right" << endl;
        cout << "4: Shoot" << endl;
        cin >> c;
        if (c == 1)
        {
            w.moveForward();
        }
        else if (c == 2)
        {
            w.turnLeft();
        }
        else if (c == 3)
        {
            w.turnRight();
        }
        else if (c == 4)
        {
            w.shoot();
        }
    }
    return 0;
}

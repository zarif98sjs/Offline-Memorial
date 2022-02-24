#include<iostream>
using namespace std;

class Unit
{
private:

    string name;
    int range,hp,cost,damage;
    int step,returnCoin;

public:

//    Unit(int r=0,int h=0,int c=0,int d=0)
//    {
//        range=r,hp=h,cost=c,damage=d;
//    }

    void setNRHCDSR(string t,int r,int h,int c,int d,int s,int rr)
    {
        name=t;
        range=r,hp=h,cost=c,damage=d;
        step=s,returnCoin=rr;
    }

    int gethp()
    {
        return hp;
    }

    string getName()
    {
        return name;
    }

    int getStep()
    {
        return step;
    }

    int getReturnCoin()
    {
        return returnCoin;
    }

    int getCost()
    {
        return cost;
    }

    int damgekorbe()
    {
        return damage;
    }

    bool isActive()
    {
        return hp>0;
    }

    void redeucedlife(int val)
    {
        hp -= val;
    }

    bool isinRange(int po)
    {
        if(100-po<=range)
            return true;
        else
            return false;
    }

    virtual void print()
    {
        return;
    }

    virtual void print2()
    {
        return;
    }

};

class Archer:public Unit
{
public:
    Archer(int x)
    {
        setNRHCDSR("Archer",50,100,150,25,25,0);
    }

    void print()
    {
        cout<<". Running. ";
    }

    void print2()
    {
        cout<<". Archer is shooting Advanced Arrow. ";
    }

};

class AdvancedArcher:public Unit
{
public:
    AdvancedArcher(int x)
    {
        setNRHCDSR("AdvancedArcher",50,120,600,50,30,0);
    }

    void print()
    {
        cout<<". Riding Horse. ";
    }

    void print2()
    {
        cout<<". Advanced Archer is shooting Improved Arrow. ";
    }

};

class Bowman:public Unit
{
public:
    Bowman(int x)
    {
        setNRHCDSR("Bowman",110,60,100,10,0,40);
    }

    void print()
    {
        cout<<". Stationary. ";
    }

    void print2()
    {
        cout<<". Bowman is shooting Basic Arrow. ";
    }

};

class AdvancedBowman:public Unit
{
public:
    AdvancedBowman(int x)
    {
        setNRHCDSR("AdvancedBowman",130,85,200,15,0,60);
    }

    void print()
    {
        cout<<". Stationary. ";
    }

    void print2()
    {
        cout<<". Advanced Bowman is shooting Canon. ";
    }

};

class EnemyTower:public Unit
{

public:

    EnemyTower()
    {
        setNRHCDSR("Enemy",200,300,0,40,0,0);
    }

};

void PlayGame(Unit &tu2,Unit &tu,int &round,int &initcoin)
{
    int enemydamage = tu2.damgekorbe();
    int unitdamage  = tu.damgekorbe();
    int pos=0;

    while(tu2.isActive() && tu.isActive())
    {
        cout<<"Round : "<<++round<<endl;

        cout<<tu.getName()<<" Health : "<<tu.gethp();
        tu.print();

        pos+=tu.getStep();
        cout<<" Positioned at "<<pos;

        if(tu.isinRange(pos))
        {
            tu2.redeucedlife(unitdamage);
            tu.print2();

        }

        cout<<endl;

        cout<<"EnemyTower Health : "<<tu2.gethp()<<". EnemyTower is shooting Fire Arrow"<<endl;

        tu.redeucedlife(enemydamage);
        //tu2.redeucedlife(unitdamage);

        if(!tu2.isActive())
        {
            //cout<<"PLAYER WINS"<<endl;
            return ;
        }

        if(!tu.isActive())
        {
            cout<<"Round : "<<++round<<endl;
            cout<<tu.getName()<<" Health : "<<tu.gethp()<<". Unit Died :) "<<endl;
            round--;
        }
    }

    initcoin+=tu.getReturnCoin();

    if(tu.getReturnCoin()>0)
    {
        cout<<tu.getName()<<" gave "<<tu.getReturnCoin()<<" while dying :("<<endl;
    }

    //cout<<"This Unit Dead, Generate new Unit"<<endl;
}

int main()
{
    Unit *w,*w2;
    w2 = new EnemyTower();
    int choice;

    int round=0;
    int initcoin=1600;

    while(1)
    {
        cout<<"Coins Remaining : "<<initcoin<<endl;
        cout<<"Your Choice: "<<endl;
        cout<<"1: Archer (Cost 150) "<<endl;
        cout<<"2: Advanced Archer (Cost 600) "<<endl;
        cout<<"3: Bowman (Cost 100) "<<endl;
        cout<<"4: Advanced Bowman (Cost 200) "<<endl;

        cin>>choice;

        switch(choice)
        {
        case 1:
            w =  new Archer(0);
            initcoin-=w->getCost();
            break;
        case 2:
            w = new AdvancedArcher(0);
            initcoin-=w->getCost();
            break;
        case 3:
            w =  new Bowman(0);
            initcoin-=w->getCost();
            break;
        default :
            w = new AdvancedBowman(0);
            initcoin-=w->getCost();
            break;
        }

        //You have to complete all the functionalities of the user using the base class pointer w.
        //That means you have to call the derived class functions using only this.

        if(initcoin<=0)
        {
            cout<<"You have spent all the coins. Computer Wins :( "<<endl;
            break;
        }

        PlayGame(*w2,*w,round,initcoin);

        if(!w2->isActive())
        {
            cout<<"You have defeated the Enemy :D Congrats. You Won"<<endl;
            break;
        }
    }

    return 0;
}

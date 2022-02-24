
int main()
{
    Unit *w;
    while(1)
    {
        switch(choice)
        {
            case 1: w =  new Archer(0);
                    break;
            case 2: w = new AdvancedArcher(0);
                    break;
            case 3: w =  new Bowman(0);
                    break;
            default : w = new AdvancedBowman(0);
                    break;
        }
        ///You have to complete all the functionalities of the user using the base class pointer w.
        ///That means you have to call the derived class functions using only this.
    }

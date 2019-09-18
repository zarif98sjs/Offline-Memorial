#include<iostream>
#include<cstring>

using namespace std;

const int nmax = 1e3+7;

class Disjoint_Set
{
    int* par;
    int* rnk;
    int siz;

public:

    Disjoint_Set()
    {
        par = new int[nmax];
        rnk = new int[nmax];
        memset(par,-1,4*nmax);
        siz = nmax;
    }

    Disjoint_Set(int num)
    {
        par = new int[num];
        rnk = new int[num];
        memset(par,-1,4*num);
        siz = num;
    }

    void Make_Set(int x)
    {
        par[x] = x;
        rnk[x] = 0;
    }

    int Find_Set(int x)
    {
        if(par[x]!=x && par[x]!=-1)
            par[x] = Find_Set(par[x]);

        return par[x];
    }

    int Find_Rep(int x)
    {
        if(par[x]==-1)
            return -1;

        if(par[x]==x)
            return x;

        return Find_Rep(par[x]);
    }

    void Union_Set(int u,int v)
    {
        int ru = Find_Set(u);
        int rv = Find_Set(v);

        if(ru==rv)
            return;

        if(rnk[rv]<rnk[ru])
            par[rv] = ru;
        else if(rnk[ru]<rnk[rv])
            par[ru] = rv;
        else
        {
            par[ru] = rv;
            rnk[rv]++;
        }
    }

    void print_set(int u)
    {
        cout<<"The Set is : ";

        int rep = Find_Rep(u);

        for(int i=0;i<siz;i++)
        {
            if(par[i]==-1)
                continue;

            int r = Find_Rep(i);

            if(r==rep)
                cout<<i<<" ";
        }

        cout<<endl;
    }

};



int main()
{
    int n,inp;
    cout<<"Disjoint Set"<<endl;
    cout<<"Number of elements : ";
    cin>>n;

    Disjoint_Set ds(n);

    while(1)
    {
        cout<<"1) Make-Set \t\t 2) Find-Set"<<endl;
        cout<<"3) Union    \t\t 4) Print"<<endl;
        cout<<"5) Exit "<<endl;

        cin>>inp;

        if(inp==1)
        {
            cout<<"Value : ";
            int x;
            cin>>x;
            ds.Make_Set(x);
        }
        else if(inp==2)
        {
            cout<<"Value : ";
            int x;
            cin>>x;
            int rep = ds.Find_Set(x);
            cout<<"Set Representative : "<<rep<<endl;
        }
        else if(inp==3)
        {
            cout<<"Give 2 Values : ";
            int x,y;
            cin>>x>>y;
            ds.Union_Set(x,y);
        }
        else if(inp==4)
        {
            cout<<"Value : ";
            int x;
            cin>>x;
            ds.print_set(x);
        }
        else
            break;
    }

    return 0;
}

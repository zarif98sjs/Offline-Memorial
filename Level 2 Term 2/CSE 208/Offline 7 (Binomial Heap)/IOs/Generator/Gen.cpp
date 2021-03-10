
/** Which of the favors of your Lord will you deny ? **/

#include<bits/stdc++.h>
using namespace std;

#define LL long long
#define PII pair<int,int>
#define PLL pair<LL,LL>
#define F first
#define S second

#define ALL(x)      (x).begin(), (x).end()
#define READ        freopen("alu.txt", "r", stdin)
#define WRITE       freopen("vorta.txt", "w", stdout)

#ifndef ONLINE_JUDGE
#define DBG(x)      cout << __LINE__ << " says: " << #x << " = " << (x) << endl
#else
#define DBG(x)
#define endl "\n"
#endif

template<class T1, class T2>
ostream &operator <<(ostream &os, pair<T1,T2>&p);
template <class T>
ostream &operator <<(ostream &os, vector<T>&v);
template <class T>
ostream &operator <<(ostream &os, set<T>&v);

inline void optimizeIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

const int nmax = 2e5+7;

int rand(int a, int b) {
    return a + rand() % (b - a + 1);
}

vector<string> operations = {"F","I","U","E"};

int MX = 1000;

int32_t main(int argc, char* argv[])
{
    optimizeIO();

    WRITE;

    srand(atoi(argv[1])); /// atoi(s) converts an array of chars to int

    int n = rand(1,MX);
    int sz = 0;

    for(int i=1;i<=n;)
    {
        int id = rand(1,MX)%4;
        string s = operations[id];

        if(s=="I")
        {
            int num = rand(1,MX);

            cout<<s<<" "<<num<<endl;
            cout<<"P"<<endl;

            i++;
            sz++;
        }
        else if(s=="F" || s=="E")
        {
            if(sz==0) continue;

            cout<<s<<endl;

            i++;
        }
        else if(s=="U")
        {
            cout<<s<<" ";

            int m = rand(1,50);

            while(m--)
            {
                int num = rand(1,MX);
                cout<<num<<" ";
            }

            cout<<endl;
            cout<<"P"<<endl;

            i++;
        }
    }

    return 0;
}

/**

**/

template<class T1, class T2>
ostream &operator <<(ostream &os, pair<T1,T2>&p)
{
    os<<"{"<<p.first<<", "<<p.second<<"} ";
    return os;
}
template <class T>
ostream &operator <<(ostream &os, vector<T>&v)
{
    os<<"[ ";
    for(T i:v)
    {
        os<<i<<" " ;
    }
    os<<" ]";
    return os;
}

template <class T>
ostream &operator <<(ostream &os, set<T>&v)
{
    os<<"[ ";
    for(T i:v)
    {
        os<<i<<" ";
    }
    os<<" ]";
    return os;
}
